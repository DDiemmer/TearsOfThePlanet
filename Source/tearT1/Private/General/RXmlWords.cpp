// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\General\RXmlWords.h"
#include "Engine/GameEngine.h"
#include <Runtime\Core\Public\Misc\FileHelper.h>
#include "Runtime/XmlParser/Public/XmlParser.h"
#include "Runtime/XmlParser/Public/XmlFile.h"
#include <Runtime\Core\Public\Misc\Paths.h>
#include <string>
#include <regex>
#include <vector>

bool URXmlWords::GetXmlTagsWord(FString FileNameA, FString tag, int lang, FString& SaveTextA)
{
	TArray<FString> TheSpawnArray;
	bool done = FFileHelper::LoadANSITextFileToStrings(*(FPaths::ProjectDir() + "wordXmls/" + FileNameA), NULL, TheSpawnArray);

	if (!done || TheSpawnArray.Num() <= 0 || tag.Len() <= 0) {
		return false;
	}

	std::string StringToSearch = std::string(TCHAR_TO_UTF8(*TheSpawnArray[0]));
	std::vector<std::string> VectorStringToReturn;

	FString tagFind = tag.ToLower();

	std::string OpeningStringToFind = "<" + std::string(TCHAR_TO_UTF8(*tagFind)) + ">";
	std::string ClosingStringToFind = "</" + std::string(TCHAR_TO_UTF8(*tagFind)) + ">";

	size_t starttag = StringToSearch.find(OpeningStringToFind);
	StringToSearch.erase(0, starttag);

	size_t endtag = StringToSearch.find(ClosingStringToFind);
	StringToSearch.erase(endtag, StringToSearch.size() - endtag);

	std::regex reg("<(.*)>([^<]*)</(\\1)>");

	TArray<FString> arraysTagString;
	const std::string& strR = StringToSearch;
	auto pos = strR.cbegin();
	auto end = strR.cend();
	std::smatch m;
	for (; std::regex_search(pos, end, m, reg); pos = m.suffix().first) {
		arraysTagString.Add(FString(m.str(2).c_str()));
	}

	if (arraysTagString.Num() >= (lang + 1)) {
		SaveTextA = arraysTagString[lang];
	}
	else if (arraysTagString.Num() > 0) {
		SaveTextA = arraysTagString[0];
	}
	else {
		SaveTextA = tag;
	}

	return true;
}
