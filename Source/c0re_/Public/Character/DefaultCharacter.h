// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "DefaultCharacter.generated.h"

/**
 * 
 */
UCLASS()
class C0RE__API ADefaultCharacter : public ABaseCharacter
{
	GENERATED_BODY()

protected:

	// Called on the server to acknowledge possession of this Character.
	virtual void PossessedBy(AController* NewController) override;

	// Called on the client when the Character is assigned it's Player State.
	virtual void OnRep_PlayerState() override;

	// Called to bind input to this Character.
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Called to set-up Ability input bindings for this Character.
	void InitializeAbilityBindings();

	bool AbilityBindingsInitialized = false;
	
};
