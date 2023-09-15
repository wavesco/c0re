// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "DefaultPlayerState.generated.h"

class UDefaultAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class C0RE__API ADefaultPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	ADefaultPlayerState();

	// The Ability System Component for this PlayerState. 
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Ability System")
	UDefaultAbilitySystemComponent* AbilitySystemComponent;

	// Implement the IAbilitySystemInterface. (This is used to find the Ability System Component)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// The Health Attribute Set on this Player State.
	UPROPERTY(BlueprintReadOnly, Category = "Ability System")
	class UHealthAttributeSet* HealthAttributes;

	// The Stamina Attribute Set on this Player State.
	UPROPERTY(BlueprintReadOnly, Category = "Ability System")
	class UStaminaAttributeSet* StaminaAttributes;
};
