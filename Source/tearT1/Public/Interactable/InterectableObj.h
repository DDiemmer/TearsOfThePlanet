// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Components/BoxComponent.h"
#include "Classes/Components/SphereComponent.h"
#include "InterectableObj.generated.h"

UCLASS()
class TEART1_API AInterectableObj : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInterectableObj();

	//toggles Item glow 
	void ToogleGlow(bool isGlowing);

	UFUNCTION()
		void EnteredObjectsRadius(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//void EnteredObjectsRadius(class AActor* OtherActor,class UPrimitiveComponents::PrimitiveComponent* OtherComp , int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweetResult);

	UFUNCTION()
		void LeavedObjectsRadius(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	   
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* SM_Interactable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UBoxComponent* BT_Interactable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USphereComponent * SC_Interactable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ColorStencil")
		int32 customStencilValue = 2;
	
public:
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
