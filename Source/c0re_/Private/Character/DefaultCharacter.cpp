// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DefaultCharacter.h"

#include "EnhancedInputComponent.h"
#include "Player/DefaultPlayerState.h"
#include "AttributeSets/HealthAttributeSet.h"
#include "AttributeSets/StaminaAttributeSet.h"
#include "AbilitySystemComponent/DefaultAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameplayAbility/GameplayAbilityBindings.h"

ADefaultCharacter::ADefaultCharacter()
{


	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

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

		InitializeAbilityBindings();
	}
}

void ADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADefaultCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADefaultCharacter::Look);

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}

	InitializeAbilityBindings();
}

void ADefaultCharacter::InitializeAbilityBindings()
{
	if (AbilityBindingsInitialized || !GetPlayerState() || !AbilitySystemComponent.Get() || !InputComponent)
	{
		return;
	}

	//AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(
	//	FString("ConfirmTarget"), 
	//	FString("CancelTarget"), 
	//	FString("EGameplayAbilityBindings"), 
	//	static_cast<int32>(EGameplayAbilityBindings::Confirm), 
	//	static_cast<int32>(EGameplayAbilityBindings::Cancel)));

	AbilityBindingsInitialized = true;
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
}

void ADefaultCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}


