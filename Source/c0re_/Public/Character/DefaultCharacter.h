// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "DefaultCharacter.generated.h"

class UInputConfig;
class UInputComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class C0RE__API ADefaultCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:

	ADefaultCharacter();

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** The input config that maps Input Actions to Input Tags*/
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputConfig* InputConfig;

protected:

	virtual void BeginPlay() override;

	// Called on the server to acknowledge possession of this Character.
	virtual void PossessedBy(AController* NewController) override;

	// Called on the client when the Character is assigned it's Player State.
	virtual void OnRep_PlayerState() override;

	// Called to bind input to this Character.
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	bool AbilityBindingsInitialized = false;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;
};
