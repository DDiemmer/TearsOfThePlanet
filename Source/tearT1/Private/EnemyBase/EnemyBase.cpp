// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\EnemyBase\EnemyBase.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,200.f, 0.f);

	eneScaleMin = 1.2f;
	eneScaleMax = 1.2f;
	eneScale = FMath::RandRange(eneScaleMin, eneScaleMax);
	UE_LOG(LogTemp, Warning, TEXT("scale =  %d"), eneScale);

}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	this->GetMesh()->SetWorldScale3D(FVector(eneScale));
	//startTransforme = GetMesh()->GetComponentTransform();
	//startTransforme  = this->GetCapsuleComponent.GetTransform();
}


// Called every frame
//void AEnemyBase::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

