// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DefaultPlayerState.h"
#include "AbilitySystemComponent/DefaultAbilitySystemComponent.h"
#include "AttributeSets/HealthAttributeSet.h"
#include "AttributeSets/StaminaAttributeSet.h"


ADefaultPlayerState::ADefaultPlayerState()
{
	// If the NetUpdateFrequency is too low, there will be a delay on Ability activation / Effect application on the client.
	NetUpdateFrequency = 60.0f;

	// Create the Ability System Component sub-object.
	AbilitySystemComponent = CreateDefaultSubobject<UDefaultAbilitySystemComponent>("Ability System Component");

	// Explicitly set the Ability System Component to replicate.
	AbilitySystemComponent->SetIsReplicated(true);

	// Sets the Ability System Component to use Full replication mode. This will replicate Gameplay Effects to everyone.
	AbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Mixed;

	// Create the Health Attribute Set sub-object.
	HealthAttributes = CreateDefaultSubobject<UHealthAttributeSet>("Health Attributes");

	// Create the Stamina Attribute Set sub-object.
	StaminaAttributes = CreateDefaultSubobject<UStaminaAttributeSet>("Stamina Attributes");
}

UAbilitySystemComponent* ADefaultPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
