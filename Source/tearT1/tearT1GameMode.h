// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "../Public/General/LanguageOp.h"
#include "GameFramework/GameModeBase.h"
#include "tearT1GameMode.generated.h"

UCLASS(minimalapi)
class AtearT1GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AtearT1GameMode();
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Language")

	UFUNCTION(BlueprintCallable, Category = "Language")
		void NextLanguage();

	UFUNCTION(BlueprintCallable, Category = "Language")
		void PreviousLanguage();

	UFUNCTION(BlueprintCallable, Category = "Language")
		int GetILanguage();

	UFUNCTION(BlueprintCallable, Category = "Language")
		FString GetSiglaLanguage();


private:
		TEnumAsByte<ELanguageOp> Language = ELanguageOp::ENGLISH;

};



