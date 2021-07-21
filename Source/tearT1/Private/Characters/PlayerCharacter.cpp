// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Engine/GameEngine.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

//returns how many points you gain when leveling up// call to initialize or sum points on leveling up
int APlayerCharacter::GetUpdateAttrPoints(EPLayerAttAcuity attrPlayerAcuity, bool firstLevel)
{
	int refAttAc = attrPlayerAcuity;
	if (firstLevel)
	{
		return (2 * this->baseAttLvUpdate) + refAttAc + this->randMaxAttLvUpdate;
	}
	int randRef = FMath::RandRange(this->randMinAttLvUpdate, this->randMaxAttLvUpdate);

	return  (randRef + baseAttLvUpdate + refAttAc);
}

void APlayerCharacter::SetPlayerAttAcuity(EPLayerAttAcuity _stAcuity, EPLayerAttAcuity _dxAcuity, EPLayerAttAcuity _constAcuity, EPLayerAttAcuity _wisAcuity, EPLayerAttAcuity _luckygAcuity)
{
	this->PlayerAttributesAcuity.stAcuity = _stAcuity;
	this->PlayerAttributesAcuity.dxAcuity = _dxAcuity;
	this->PlayerAttributesAcuity.constAcuity = _constAcuity;
	this->PlayerAttributesAcuity.wisAcuity = _wisAcuity;
	this->PlayerAttributesAcuity.luckyAcuity = _luckygAcuity;
}

int APlayerCharacter::GetUpdateStPoints()
{
	return GetUpdateAttrPoints(this->PlayerAttributesAcuity.stAcuity, this->PlayerBasicAttributes.strong == 0);
}

int APlayerCharacter::GetUpdateDxPoints()
{
	return GetUpdateAttrPoints(this->PlayerAttributesAcuity.dxAcuity, this->PlayerBasicAttributes.dexterity == 0);
}

int APlayerCharacter::GetUpdateConstPoints()
{
	return GetUpdateAttrPoints(this->PlayerAttributesAcuity.constAcuity, this->PlayerBasicAttributes.constitution == 0);
}

int APlayerCharacter::GetUpdateWisPoints()
{
	return GetUpdateAttrPoints(this->PlayerAttributesAcuity.wisAcuity, this->PlayerBasicAttributes.wisdom == 0);
}

int APlayerCharacter::GetUpdateLuckyPoints()
{
	return GetUpdateAttrPoints(this->PlayerAttributesAcuity.luckyAcuity, this->PlayerBasicAttributes.lucky == 0);
}

int APlayerCharacter::GetUpHealthPoints()
{
	//first level inst 
	if (this->PlayerBasicAttributes.maxHealth == 0) {
		//min health + curr const points + acuity * acuity 
		return this->minStartHealth + this->PlayerBasicAttributes.constitution + ((int)this->PlayerAttributesAcuity.constAcuity * (int)this->PlayerAttributesAcuity.constAcuity);
	}

	//base on constitution points / 10
	int baseAdd = FMath::RoundToInt(this->PlayerBasicAttributes.constitution / 10);
	//sum to const acuity 
	baseAdd += (int)this->PlayerAttributesAcuity.constAcuity;

	return baseAdd;
}

int APlayerCharacter::GetUpNatureSyncPoints()
{
	//first level inst 
	if (this->PlayerBasicAttributes.maxNatureSync == 0) {
		//min nature sync + curr wisdom points + acuity * acuity 
		return this->minStartNatureSync + this->PlayerBasicAttributes.wisdom + ((int)this->PlayerAttributesAcuity.wisAcuity * (int)this->PlayerAttributesAcuity.wisAcuity);
	}
	//base on wisdom points /  ((max Acuity + 2 - wisdowAcuity )* 10)
	int baseAdd = FMath::RoundToInt(this->PlayerBasicAttributes.wisdom / ((((int)EPLayerAttAcuity::EXCELLENT) + 2 - (int)this->PlayerAttributesAcuity.wisAcuity) * 10));

	return baseAdd;
}

void APlayerCharacter::onSetXp(int32 xpGain)
{
	if (xpGain > 0) {
		//keep old result to safe or show differences maybe 
		int32 currXp = this->PlayerInfos.xp;
		int32 currLevel = this->PlayerInfos.level;

		//update xp 
		this->PlayerInfos.xp += xpGain;
		//calc if update to next level 
		//
		float b = baseXpUpdateLv;
		float a = b / 2;
		float c = this->PlayerInfos.xp * -1;
		//a² + b + c = 0 
		// ((-b + sqtr(b² - (4.a.c))) /2.a )  
		float CalcLevel = 1 + ((-b + FMath::Sqrt(FMath::Square(b) - (4 * a * c))) / (2 * a));
		
		GEngine->AddOnScreenDebugMessage(-1, 1000.0f, FColor::Red, FString::Printf(TEXT("caalcLevel : %f"),CalcLevel));
	
		bool levelUp = FMath::TruncToInt(CalcLevel) > this->PlayerInfos.level;
		if (levelUp) {
			//level up 
			//verify how many levels ups 
			int levelsUp = FMath::TruncToInt(CalcLevel) - this->PlayerInfos.level;
			this->PlayerInfos.level += levelsUp;
		}
		//the number after dot multiply 100  = percent of this level ex: actual level 1 and calc level equal 1.36, 1.36 - 1 = 0.36 * 100 = 36%
		this->PlayerInfos.percentNextLevel = (CalcLevel - this->PlayerInfos.level);
		GEngine->AddOnScreenDebugMessage(-1, 1000.0f, FColor::Red, FString::Printf(TEXT("percente : %f"),this->PlayerInfos.percentNextLevel));
	}

	//calc how much xp is missing for next level
	int xpNextLevel = ((((baseXpUpdateLv * (this->PlayerInfos.level + 2))) * this->PlayerInfos.level) / 2);
	//ex:base equal 200 level equal 4 Xpnext =  (200+(200 * level + 1)* level)/2) =  ((200 * level + 2)* level)/2)
	this->PlayerInfos.nextLevelXp = xpNextLevel;
}
