// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/Interactable/InterectableObj.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Engine/GameEngine.h"
#include "tearT1.h"

// Sets default values
AInterectableObj::AInterectableObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SM_Interactable = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMInteractable"));

	BT_Interactable = CreateDefaultSubobject<UBoxComponent>(TEXT("BTInteractable"));

	SC_Interactable = CreateDefaultSubobject<USphereComponent>(TEXT("SCInteractable"));
}
// Called when the game starts or when spawned
void AInterectableObj::BeginPlay()
{
	Super::BeginPlay();

	BT_Interactable->SetGenerateOverlapEvents(true);
	BT_Interactable->OnComponentBeginOverlap.AddDynamic(this,&AInterectableObj::EnteredObjectsRadius);
	BT_Interactable->OnComponentEndOverlap.AddDynamic(this, &AInterectableObj::LeavedObjectsRadius);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Begin ObjInt")));
	SM_Interactable->SetCustomDepthStencilValue(int32(customStencilValue));

}
void AInterectableObj::EnteredObjectsRadius(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Call entered")));
	ToogleGlow(true);
}

void AInterectableObj::LeavedObjectsRadius(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Call Leave")));
	ToogleGlow(false);
}

void AInterectableObj::ToogleGlow(bool isGlowing) {

	SM_Interactable->SetRenderCustomDepth(isGlowing);
}




