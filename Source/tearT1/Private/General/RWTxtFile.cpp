// Fill out your copyright notice in the Description page of Project Settings.


#include "../..//Public/General/RWTxtFile.h"
#include <Runtime\Core\Public\Misc\FileHelper.h>
#include <Runtime\Core\Public\Misc\Paths.h>


bool URWTxtFile::LoadTxt(FString FileNameA, FString& SaveTextA)
{
	return FFileHelper::LoadFileToString(SaveTextA, *(FPaths::GameDir() + FileNameA));
}

bool URWTxtFile::SaveTxt(FString SaveTextB, FString FileNameB)
{
	return FFileHelper::SaveStringToFile(SaveTextB, *(FPaths::GameDir() + FileNameB));
}
