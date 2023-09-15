// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefaultPlayerController.generated.h"

class UInputComponent;
class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class C0RE__API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()

public:


protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	virtual void BeginPlay() override;

};
