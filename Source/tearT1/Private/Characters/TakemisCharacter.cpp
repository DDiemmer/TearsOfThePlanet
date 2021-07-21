// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\Characters\TakemisCharacter.h"
#include "..\..\Public\Characters\PlayerCharacter.h"
#include "Engine/GameEngine.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include <string>

ATakemisCharacter::ATakemisCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	ATakemisCharacter::SetInitialAttributes();

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}
//initial att
void ATakemisCharacter::SetInitialAttributes()
{

	//7 pontos a soma dos accuits
	ATakemisCharacter::SetPlayerAttAcuity(EPLayerAttAcuity::REGULAR, EPLayerAttAcuity::GOOD, EPLayerAttAcuity::REGULAR, EPLayerAttAcuity::GOOD, EPLayerAttAcuity::REGULAR);
	//set attributs 
	PlayerBasicAttributes.strong += ATakemisCharacter::GetUpdateStPoints();
	PlayerBasicAttributes.dexterity += ATakemisCharacter::GetUpdateDxPoints();
	PlayerBasicAttributes.constitution += ATakemisCharacter::GetUpdateConstPoints();
	PlayerBasicAttributes.wisdom += ATakemisCharacter::GetUpdateWisPoints();
	PlayerBasicAttributes.lucky += ATakemisCharacter::GetUpdateLuckyPoints();
	//set health 
	PlayerBasicAttributes.maxHealth += ATakemisCharacter::GetUpHealthPoints();
	PlayerBasicAttributes.currHealth = this->PlayerBasicAttributes.maxHealth;
	//set Nature Sync 
	PlayerBasicAttributes.maxNatureSync += ATakemisCharacter::GetUpNatureSyncPoints();
	PlayerBasicAttributes.currNatureSync = this->PlayerBasicAttributes.maxNatureSync;
	//Set Stamina bar 

	//Set Stamina time regain
	PlayerBasicPreviousAttributes = PlayerBasicAttributes;

	ATakemisCharacter::SetPlayerInfo();

}

void ATakemisCharacter::SetPlayerInfo()
{
	PlayerInfos.name = "Takemis Goukai";
	PlayerInfos.label = "Takemis";

	PlayerInfos.description = "...long history...";
	//calcula level update percent and next level up xp 
	ATakemisCharacter::onSetXp(0);
}


// Called when the game starts or when spawned
void ATakemisCharacter::BeginPlay()
{
	Super::BeginPlay();

	////verificar initial sets 
	//GEngine->AddOnScreenDebugMessage(-1, 1000.0f, FColor::Red, FString::Printf(TEXT("Player lucky : %i"),(int)PlayerBasicAttributes.lucky));
	//GEngine->AddOnScreenDebugMessage(-1, 1000.0f, FColor::Red, FString::Printf(TEXT("Player wisdom : %i"), (int)PlayerBasicAttributes.wisdom));
	//GEngine->AddOnScreenDebugMessage(-1, 1000.0f, FColor::Red, FString::Printf(TEXT("Player constitution : %i"), (int)PlayerBasicAttributes.constitution));
	//GEngine->AddOnScreenDebugMessage(-1, 1000.0f, FColor::Red, FString::Printf(TEXT("Player dexterity : %i"), (int)PlayerBasicAttributes.dexterity));
	//GEngine->AddOnScreenDebugMessage(-1, 1000.0f, FColor::Red, FString::Printf(TEXT("Player strong : %i"), (int)PlayerBasicAttributes.strong));
	//GEngine->AddOnScreenDebugMessage(-1, 1000.0f, FColor::Red, FString::Printf(TEXT("Player Max Nature Sync : %i"), (int)PlayerBasicAttributes.maxNatureSync));
	//GEngine->AddOnScreenDebugMessage(-1, 1000.0f, FColor::Red, FString::Printf(TEXT("Player Max Health : %i"), (int)PlayerBasicAttributes.maxHealth));
	//GEngine->AddOnScreenDebugMessage(-1, 1000.0f, FColor::Red, FString::Printf(TEXT("next level xp: %i"), (int)PlayerInfos.nextLevelXp));
	//FString test = PlayerInfos.name;
	//std::string test2 = std::string(TCHAR_TO_UTF8(*test));
	////UE_LOG(LogTemp, Warning, TEXT("JSON %s"), *FString(test2.c_str()));

	//GEngine->AddOnScreenDebugMessage(-1, 1000.0f, FColor::Green, FString::Printf(TEXT("Player name : %s"), *FString(test2.c_str())));

}


// Called to bind functionality to input
void ATakemisCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATakemisCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATakemisCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATakemisCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATakemisCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ATakemisCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ATakemisCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ATakemisCharacter::OnResetVR);
}

void ATakemisCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ATakemisCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ATakemisCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ATakemisCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATakemisCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATakemisCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATakemisCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

