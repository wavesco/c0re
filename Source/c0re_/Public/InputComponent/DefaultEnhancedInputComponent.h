// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "GameplayTagContainer.h"
#include "Input/InputConfig.h"
#include "DefaultEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class C0RE__API UDefaultEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
 
	template<class UserClass, typename FuncType>
	void BindActionByTag(const UInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func);
};
 
template<class UserClass, typename FuncType>
void UDefaultEnhancedInputComponent::BindActionByTag(const UInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
{
	check(InputConfig);
	if (const UInputAction* IA = InputConfig->FindInputActionForTag(InputTag))
	{
		BindAction(IA, TriggerEvent, Object, Func);
	}
	
};
