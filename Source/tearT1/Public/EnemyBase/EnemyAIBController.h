// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "EnemyBase.h"
#include "EnemyAIBController.generated.h"

/**
 *
 */
UCLASS()
class TEART1_API AEnemyAIBController : public AAIController
{
	GENERATED_BODY()

private:

	FTransform startTransforme;

	AEnemyBase* EnemyBase;

protected:

	FTimerHandle _loopTimeHandle;

	FTimerHandle _loopTimeToTickHandle;

	bool returnPosition = false;

	bool bSeekingPlayer = false;

	bool bOnRotationToBack = false;

	bool bOnPatrol = false;

	FVector LocPatrol;

public:
	AEnemyAIBController();

	virtual void BeginPlay() override;

	/*virtual void OnPossess(APawn* InPawn) override;*/

	//virtual void Tick(float DeltaSeconds) override;

	virtual FRotator GetControlRotation() const override;

	UFUNCTION(Category = "Perception")
		void OnPawnDetected(const TArray<AActor*>& DetectedPawns);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightRadius = 900.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightAge = 5.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AILoseSight = AISightRadius + 2500.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightFieldOfView = 45.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		class  UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		bool bIsPlayerDetected = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float DistanceToPlayer = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float patrolDistance = 2500.f;

	UFUNCTION()
		void OnTimerEnd();

	UFUNCTION()
		void OnTimertoTickEnd();

	void OnFinishedMoviment(FAIRequestID RequestID, const FPathFollowingResult& Result);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float closeRangeValue = 450.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float LongRangeValue = 2000.f;

	//UFUNCTION(BlueprintCallable, Category = "Action Range")
	//	static void onCloseRange();

	//UFUNCTION(BlueprintCallable, Category = "Action Range")
	//	static void onLongRange();
	//UFUNCTION()
	//	void CounterLoop();

};
