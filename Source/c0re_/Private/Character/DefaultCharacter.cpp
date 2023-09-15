// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DefaultCharacter.h"
#include "Player/DefaultPlayerState.h"
#include "AttributeSets/HealthAttributeSet.h"
#include "AttributeSets/StaminaAttributeSet.h"
#include "AbilitySystemComponent/DefaultAbilitySystemComponent.h"
#include "GameplayAbility/GameplayAbilityBindings.h"

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

void ADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InitializeAbilityBindings();
}
