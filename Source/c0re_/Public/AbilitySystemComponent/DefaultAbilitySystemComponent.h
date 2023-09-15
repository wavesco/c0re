// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DefaultAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class C0RE__API UDefaultAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	UDefaultAbilitySystemComponent();
	
	// Have the owning Character's Default Abilities been given yet?
	bool DefaultAbilitiesGiven = false;

	// Have the owning Character's Default Effects been applied yet?
	bool DefaultEffectsApplied = false;
};
