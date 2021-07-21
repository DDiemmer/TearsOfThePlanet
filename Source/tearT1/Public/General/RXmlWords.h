// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RXmlWords.generated.h"

/**
 *
 */
UCLASS()
class TEART1_API URXmlWords : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintPure, Category = "XmlReader", meta = (Keywords = "GetXmlTagWord"))
		static bool GetXmlTagsWord(FString FileNameA,FString tag, int lang, FString& SaveTextA);

};
