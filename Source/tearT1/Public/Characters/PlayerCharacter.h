// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerAtt.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class TEART1_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//player infos 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player infos")
		FPlayerInfos PlayerInfos;
	//basic current attributes 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Basic Attributes")
		FPlayerAttributes PlayerBasicAttributes;
	//basic previous attributes to show updates aftes leveling up
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Basic Attributes")
		FPlayerAttributes PlayerBasicPreviousAttributes;

	//set Xp and nivel 
	UFUNCTION(BlueprintCallable,Category = "Att Actions")
		void onSetXp(int32 xpGain);

	//acuity att
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Attributes Acuity")
		FPlayerAttributesAcuity PlayerAttributesAcuity;
	
	//set acuity on attributes 
	void SetPlayerAttAcuity(EPLayerAttAcuity _stAcuity, EPLayerAttAcuity _dxAcuity, EPLayerAttAcuity _constAcuity, EPLayerAttAcuity _wisAcuity, EPLayerAttAcuity _luckygAcuity);
	//get attribute points 
	//get St points
	int GetUpdateStPoints();
	//get Dx points
	int GetUpdateDxPoints();
	//get Const points
	int GetUpdateConstPoints();
	//get Wis points
	int GetUpdateWisPoints();
	//get Lucky points
	int GetUpdateLuckyPoints();
	//get health points to add
	int GetUpHealthPoints();
	//get Nature Sync points to add
	int GetUpNatureSyncPoints();
public:
	// Called every frame
	/*virtual void Tick(float DeltaTime) override;*/

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	int GetUpdateAttrPoints(EPLayerAttAcuity attrPlayerAcuity, bool firstLevel = false);
	
	int32 baseXpUpdateLv = 200;

	int32 minStartHealth = 30;

	int32 minStartNatureSync = 30;

	//to help update attributes 
	int baseAttLvUpdate = 4;

	int randMaxAttLvUpdate = 2;

	int randMinAttLvUpdate = -2;

};

