// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility/DefaultGameplayAbility.h"
#include "AbilitySystemComponent.h"			
#include "FunctionLibrary/AbilitySystemFunctionLibrary.h"

float UDefaultGameplayAbility::GetModifiedAbilityStrength()
{
	float BaseStrength = BaseAbilityStrength.GetValueAtLevel(GetAbilityLevel());

	if (const UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo())
	{
		for (const FAbilityModifierStruct Modifier : AbilityModifiers)
		{
			if (const float AttributeValue = UAbilitySystemFunctionLibrary::GetAttributeValueFromAbilitySystem(AbilitySystemComponent, Modifier.BackingAttribute, Modifier.AttributeSearchType) != -1.0f)
			{
				BaseStrength += AttributeValue * Modifier.AttributeModifier;
			}
		}
	}
	
	return BaseStrength;
}

void UDefaultGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (ActivateAbilityOnGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}

UDefaultGameplayAbility::UDefaultGameplayAbility()
{
	// Sets the ability to default to Instanced Per Actor.
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;	
}
