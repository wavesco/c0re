// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DefaultCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "Player/DefaultPlayerState.h"
#include "AttributeSets/HealthAttributeSet.h"
#include "AttributeSets/StaminaAttributeSet.h"
#include "AbilitySystemComponent/DefaultAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameplayTags/DefaultGameplayTags.h"
#include "InputComponent/DefaultEnhancedInputComponent.h"

ADefaultCharacter::ADefaultCharacter()
{

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent()); // Attach the camera to the capsule
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

}

void ADefaultCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

void ADefaultCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (ADefaultPlayerState* DefaultPlayerState = Cast<ADefaultPlayerState>(GetPlayerState()))
	{
		AbilitySystemComponent = DefaultPlayerState->AbilitySystemComponent;

		// Set the Owner and Avatar actor for the Ability System Component. (On the Server)
		AbilitySystemComponent->InitAbilityActorInfo(DefaultPlayerState, this);

		HealthAttributes = DefaultPlayerState->HealthAttributes;

		StaminaAttributes = DefaultPlayerState->StaminaAttributes;

		ApplyDefaultEffects();
	}
}

void ADefaultCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (ADefaultPlayerState* DefaultPlayerState = Cast<ADefaultPlayerState>(GetPlayerState()))
	{
		AbilitySystemComponent = DefaultPlayerState->AbilitySystemComponent;

		// Set the Owner and Avatar actor for the Ability System Component. (On the Client)
		AbilitySystemComponent->InitAbilityActorInfo(DefaultPlayerState, this);

		HealthAttributes = DefaultPlayerState->HealthAttributes;

		StaminaAttributes = DefaultPlayerState->StaminaAttributes;
	}
}

void ADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UDefaultEnhancedInputComponent* DefaultEnhancedInputComponent = Cast<UDefaultEnhancedInputComponent>(PlayerInputComponent))
	{
		check(DefaultEnhancedInputComponent);

		const FDefaultGameplayTags& GameplayTags = FDefaultGameplayTags::Get();

		// Moving
		DefaultEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.IT_Move, ETriggerEvent::Triggered, this, &ADefaultCharacter::Move);

		// Looking
		DefaultEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.IT_LookMouse, ETriggerEvent::Triggered, this, &ADefaultCharacter::Look);

		// Jumping
		DefaultEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.IT_Jump,ETriggerEvent::Started, this, &ACharacter::Jump);
		DefaultEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.IT_Jump,ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
}

void ADefaultCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}

	UE_LOG(LogTemp, Warning, TEXT("LookAxisVector: %s"), *LookAxisVector.ToString());
}

void ADefaultCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// add movement 
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);

	UE_LOG(LogTemp, Warning, TEXT("MovementVector: %s"), *MovementVector.ToString());
	UE_LOG(LogTemp, Warning, TEXT("GetActorForwardVector(): %s"), *GetActorForwardVector().ToString());
	UE_LOG(LogTemp, Warning, TEXT("GetActorRightVector(): %s"), *GetActorRightVector().ToString());
}


