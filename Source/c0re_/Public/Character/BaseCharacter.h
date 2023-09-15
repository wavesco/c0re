// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS(Abstract, NotBlueprintable)
class C0RE__API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Implement the IAbilitySystemInterface. (This is used to find the Ability System Component)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// The default Abilities this Character has access to.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability System")
	TArray<TSubclassOf<class UDefaultGameplayAbility>> DefaultAbilities;

	// The default gameplay Effects this Character has when spawned.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability System")
	TArray<TSubclassOf<class UGameplayEffect>> DefaultEffects;

	// Called automatically by the Health Attribute Set when "Current Health" reaches zero.
	void OnDeath();
	
	// Event called when the the Current Health attribute reaches zero.
	// Note: This will only be called with Authority.
	UFUNCTION(BlueprintImplementableEvent, Category = "Character Base")
	void On_Death();

protected:
	// Creates a pointer to the Ability System Component associated with this Character.
	// Player Characters will set this in OnRep_PlayerState() locally, and in OnPossessed() server side.
	// Non Player Characters will set this in its constructor.
	TWeakObjectPtr<class UDefaultAbilitySystemComponent> AbilitySystemComponent;

	// Creates a pointer to the Health Attribute Set associated with this Character.
	// Player Characters will set this in OnRep_PlayerState() locally, and in OnPossessed() server side.
	// Non Player Characters will set this in its constructor.
	TWeakObjectPtr<class UHealthAttributeSet> HealthAttributes;

	// Creates a pointer to the Stamina Attribute Set associated with this Character.
	// Player Characters will set this in OnRep_PlayerState() locally, and in OnPossessed() server side.
	// Non Player Characters will set this in its constructor.
	TWeakObjectPtr<class UStaminaAttributeSet> StaminaAttributes;

	// Called to give the Character it's Default Abilities from the "Default Abilities" array.
	void GiveDefaultAbilities();

	// Called to apply the Gameplay Effects in the "Default Effects" array.
	void ApplyDefaultEffects();

};
