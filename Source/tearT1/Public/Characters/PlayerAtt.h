// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "../../Public/Characters/PlayerAtt.h"
#include "PlayerAtt.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum EPLayerAttAcuity
{
	//UMETA(DisplayName = "Bad Acuity")
	BAD = 0,
	REGULAR = 1,
	GOOD = 2,
	EXCELLENT = 3,
};

USTRUCT(BlueprintType)
struct FPlayerAttributes {

	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Basic Attributes")
		int32 maxHealth = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Basic Attributes")
		int32 currHealth = 0;
	//like mp to use nature magics 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Basic Attributes")
		int32 maxNatureSync = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Basic Attributes")
		int32 currNatureSync = 0;
	//to physical base dmg
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Basic Attributes")
		int32 strong = 0;
	//to defense and dodge
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Basic Attributes")
		int32 dexterity = 0;
	//to gain more life on level up 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Basic Attributes")
		int32 constitution = 0;
	//give so much natureSync up for level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Basic Attributes")
		int32 wisdom = 0;
	//to find itens and etc 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Basic Attributes")
		int32 lucky = 0;
	//to move and attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Basic Attributes")
		int32 staminaBar = 0;
	//determine how fast regain 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Basic Attributes")
		int32 staminaTimeRegain = 0;
};


USTRUCT(BlueprintType)
struct FPlayerAttributesAcuity {

	GENERATED_USTRUCT_BODY()
		///Attribute Acuity
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Att Acuity")
		TEnumAsByte<EPLayerAttAcuity> stAcuity = EPLayerAttAcuity::REGULAR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Att Acuity")
		TEnumAsByte<EPLayerAttAcuity> dxAcuity = EPLayerAttAcuity::REGULAR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Att Acuity")
		TEnumAsByte<EPLayerAttAcuity> constAcuity = EPLayerAttAcuity::REGULAR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Att Acuity")
		TEnumAsByte<EPLayerAttAcuity> wisAcuity = EPLayerAttAcuity::REGULAR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Att Acuity")
		TEnumAsByte<EPLayerAttAcuity> luckyAcuity = EPLayerAttAcuity::REGULAR;

};


USTRUCT(BlueprintType)
struct FPlayerInfos {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Infos")
		FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Infos")
		FString label;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Infos")
		FString description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Infos")
		int32 level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Infos")
		int32 xp = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Infos")
		float percentNextLevel = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Infos")
		int32 nextLevelXp = 0.f;

};