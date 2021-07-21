// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "tearT1GameMode.h"
#include "tearT1Character.h"
#include "Engine/GameEngine.h"
#include "TakemisCharacter.generated.h"
#include "UObject/ConstructorHelpers.h"
#include <string>

AtearT1GameMode::AtearT1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/MyContents/Takemis/Blueprints/TakemisCharacterBP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;

	}
	//FString test = FPaths::ProjectDir() ;
	//std::string test2 = std::string(TCHAR_TO_UTF8(*test));
	////UE_LOG(LogTemp, Warning, TEXT("JSON %s"), *FString(test2.c_str()));
	//GEngine->AddOnScreenDebugMessage(-1, 1000.0f, FColor::Green, FString::Printf(TEXT("Project Dir : %s"), *FString(test2.c_str())));
	
}

void AtearT1GameMode::NextLanguage()
{
	if (Language >= ELanguageOp::MAXLANG)
		Language = ELanguageOp::MINLANG;
	else
		Language = (ELanguageOp)(Language + 1);

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Next Lang: %i"),(int)Language));
}

void AtearT1GameMode::PreviousLanguage()
{
	if (Language <= ELanguageOp::MINLANG)
		Language = ELanguageOp::MAXLANG;
	else
		Language = (ELanguageOp)(Language - 1);

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Previous Lang: %i"), (int)Language));
}

int AtearT1GameMode::GetILanguage()
{
	return (int)Language;
}

FString AtearT1GameMode::GetSiglaLanguage()
{
	switch (Language)
	{
	case ELanguageOp::PORTUGUESE:
		return FString("Pt-Br");

	case ELanguageOp::ENGLISH:
		return FString("En-Br");
	
	default:
		break;
	}

	return FString("");
}
