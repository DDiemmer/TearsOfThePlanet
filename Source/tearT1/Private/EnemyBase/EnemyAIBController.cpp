// Fill out your copyright notice in the Description page of Project Settings.

#include "../../Public/EnemyBase/EnemyAIBController.h"
#include "Engine/GameEngine.h"
#include "tearT1.h"
#include "TakemisCharacter.h"
#include "EnemyBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h" //Where FPathFollowingResult lives
#include "AITypes.h" //Where FAIRequestID lives

AEnemyAIBController::AEnemyAIBController()
{

	PrimaryActorTick.bCanEverTick = false;

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	SetPerceptionComponent(*(CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"))));
	PerceptionComponent = GetPerceptionComponent();

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSight;
	SightConfig->PeripheralVisionAngleDegrees = AISightFieldOfView;
	SightConfig->SetMaxAge(AISightAge);


	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());


}

void AEnemyAIBController::BeginPlay() {
	Super::BeginPlay();


	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, UAISense_Sight::StaticClass(), this);

	GetPerceptionComponent()->RequestStimuliListenerUpdate();


	UAIPerceptionComponent* PerceptionComp = GetPerceptionComponent();
	if (PerceptionComp)
	{

		PerceptionComp->ConfigureSense(*SightConfig);
		PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());

		PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIBController::OnPawnDetected);
	}

	//startTransforme = GetMesh()->GetComponentTransform();

	if (GetPerceptionComponent() != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("EnemyAi Controller Seted "));

		FString name = GetPawn()->GetName();

		//	UE_LOG(LogTemp, Warning, TEXT("PawnName %s"),name);
		//  GetEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, "Perception Sense Updated");
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Deu galho"));
	}

	UPathFollowingComponent* PathFollowingComponent = this->GetPathFollowingComponent();
	PathFollowingComponent->OnRequestFinished.AddUObject(this, &AEnemyAIBController::OnFinishedMoviment);

	startTransforme = GetPawn()->GetActorTransform();
	
	EnemyBase = Cast<AEnemyBase>(this->GetCharacter());

	//add 5 to adjust rotation 
	LocPatrol = (startTransforme.GetRotation().GetForwardVector() * (patrolDistance + 10.f)) + startTransforme.GetLocation();

	bOnPatrol = true;

	if (patrolDistance > 0.f)
	{
		float randStartPatrolSeed = FMath::RandRange(1, 5);
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Patrol em %f sec"), randStartPatrolSeed));
		GetWorld()->GetTimerManager().SetTimer(_loopTimeHandle, this, &AEnemyAIBController::OnTimerEnd, randStartPatrolSeed, false);
	}
	//SetTimer(_loopTimeHandle,this, &AEnemyAIBController::OnTimerEnd,5.f,false);
}

//void AEnemyAIBController::OnPossess(APawn* InPawn) {
//	Super::Possess(InPawn);
//	
//}

//void AEnemyAIBController::Tick(float DeltaSeconds) {
//	Super::Tick(DeltaSeconds);
//}
void AEnemyAIBController::OnTimertoTickEnd() {

	if (bIsPlayerDetected) {
		ATakemisCharacter* Takemis = Cast<ATakemisCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		DistanceToPlayer = GetPawn()->GetDistanceTo(Takemis);
		///update distance
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("chamou move to player1")));
		this->MoveToActor(Takemis, 5.f);

		if (DistanceToPlayer > AILoseSight) {
			bIsPlayerDetected = false;

			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("startTimer")));
			//start delay to stop follow 
			GetWorld()->GetTimerManager().SetTimer(_loopTimeHandle, this, &AEnemyAIBController::OnTimerEnd, 5.f, false);
		}
		else if(EnemyBase != nullptr){
			
			if (!EnemyBase->isInActionRange) {
				FOutputDevice* ar = NULL;
				if (DistanceToPlayer < closeRangeValue)
				{
					this->GetCharacter()->CallFunctionByNameWithArguments(TEXT("CloseRange"), *ar, NULL, true);
					//this->CallFunctionByNameWithArguments(TEXT("CloseRange"),ar,NULL,true);
				}
				else if (DistanceToPlayer < LongRangeValue)
				{
					this->GetCharacter()->CallFunctionByNameWithArguments(TEXT("LongRange"), *ar, NULL, true);
					//this->CallFunctionByNameWithArguments(TEXT("LongRange"),*ar, NULL, true);
				}
			}
		}
	}
}

void AEnemyAIBController::OnTimerEnd() {

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "debug msg times over ");
	//UE_LOG(LogTemp, Warning, TEXT("timeover?"));

	///still seek player to more sec 
	if (bSeekingPlayer)
	{
		bSeekingPlayer = false;
		bOnPatrol = false;
		returnPosition = true;
		this->StopMovement();
		//paro o tick do loop de game aqui 
		GetWorld()->GetTimerManager().ClearTimer(_loopTimeToTickHandle);
		//aguarda xsec and back to start position 
		GetWorld()->GetTimerManager().SetTimer(_loopTimeHandle, this, &AEnemyAIBController::OnTimerEnd, 3.f, false);
	}
	//back to start pos after some time 
	else if (returnPosition) {
		this->MoveToLocation(startTransforme.GetLocation(), 5.f);
	}
	else if (bOnPatrol) {
		this->MoveToLocation(LocPatrol, 5.f);
	}
	else {
		///varificar se a rotacao eh igual a inicial e girar ate q fique igual 
	}
}

FRotator AEnemyAIBController::GetControlRotation() const
{
	if (GetPawn() == nullptr) {
		return FRotator(0.0f, 0.0f, 0.0f);
	}
	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void  AEnemyAIBController::OnPawnDetected(const TArray<AActor*>& DetectedPawns) {

	//UE_LOG(LogTemp, Warning, TEXT("Player detected Distance: %d"), DetectedPawns.Num());
	for (size_t i = 0; i < DetectedPawns.Num(); i++)
	{
	//	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("detectou algo ?")));
		if (DetectedPawns[i] == GetWorld()->GetFirstPlayerController()->GetPawn()) {
			DistanceToPlayer = GetPawn()->GetDistanceTo(DetectedPawns[i]);
			//first sight ....
			if (DistanceToPlayer <= AISightRadius) {
				bIsPlayerDetected = true;
				bSeekingPlayer = true;
				returnPosition = false;
				bOnPatrol = false;
				//UE_LOG(LogTemp, Warning, TEXT("Player detected Distance: %f"), DistanceToPlayer);
				//inicio o timer que roda no lugar do tick 
				GetWorld()->GetTimerManager().SetTimer(_loopTimeToTickHandle, this, &AEnemyAIBController::OnTimertoTickEnd, 0.3f, true);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("nao eh o player controle"));
		}
	}
}

void AEnemyAIBController::OnFinishedMoviment(FAIRequestID RequestID, const FPathFollowingResult& Result) {

	if (Result.IsSuccess()) {
		if (returnPosition) {
			returnPosition = false;
			bOnPatrol = true;
			StopMovement();
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("finishou o bagulho o bagulho certo agora ")));
			GetWorld()->GetTimerManager().SetTimer(_loopTimeHandle, this, &AEnemyAIBController::OnTimerEnd, 3.f, false);
		}
		else if (bOnPatrol) {
			bOnPatrol = false;
			//if patrolDistance equal zero, use just to adjust rotation position 
			if (patrolDistance > 0.f)
			{
				returnPosition = true;
				//just to teste performance between BP e c++
				//this->CounterLoop();
			}

			StopMovement();
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("finishou o patrol ")));
			GetWorld()->GetTimerManager().SetTimer(_loopTimeHandle, this, &AEnemyAIBController::OnTimerEnd, 2.7f, false);
		}
	}
	else if (Result.IsFailure()) {
		if (!bIsPlayerDetected) {
			bSeekingPlayer = false;
			bIsPlayerDetected = false;
			bOnPatrol = false;
			returnPosition = true;
			StopMovement();
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Bugou tudo.... melhor retornar ")));
			GetWorld()->GetTimerManager().SetTimer(_loopTimeHandle, this, &AEnemyAIBController::OnTimerEnd, 3.f, false);
		}
		else {
			bOnPatrol = false;
			returnPosition = false;
		}
	}
}
//
//void AEnemyAIBController::CounterLoop() {
//
//	float static timeBefore = UGameplayStatics::GetRealTimeSeconds(GetWorld());
//	float counter = 0;
//	for (int j = 0; j < 1000000; j++)
//	{
//		ATakemisCharacter* Takemis = Cast<ATakemisCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
//		DistanceToPlayer = GetPawn()->GetDistanceTo(Takemis);
//		counter++;
//	}
//	float static timeAfter = UGameplayStatics::GetRealTimeSeconds(GetWorld());
//
//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("c++ coontou  %f"), counter));
//}
