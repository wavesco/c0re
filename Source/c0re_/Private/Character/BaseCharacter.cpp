// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "AbilitySystemComponent/DefaultAbilitySystemComponent.h"
#include "GameplayAbility/DefaultGameplayAbility.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

void ABaseCharacter::GiveDefaultAbilities()
{
	if (AbilitySystemComponent->DefaultAbilitiesGiven || GetLocalRole() != ROLE_Authority)
	{
		return;
	}
	
	for (TSubclassOf<UDefaultGameplayAbility>& DefaultAbility : DefaultAbilities)
	{
		if (IsValid(DefaultAbility))
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(DefaultAbility, 1, static_cast<int32>(DefaultAbility.GetDefaultObject()->InputBinding), this));
		}
	}

	AbilitySystemComponent->DefaultAbilitiesGiven = true;
}

void ABaseCharacter::ApplyDefaultEffects()
{
	if (AbilitySystemComponent->DefaultEffectsApplied || GetLocalRole() != ROLE_Authority)
	{
		return;
	}

	for (TSubclassOf<UGameplayEffect> Effect : DefaultEffects)
	{
		if (IsValid(Effect))
		{
			FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
			EffectContextHandle.AddSourceObject(this);

			FGameplayEffectSpecHandle GameplayEffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 1, EffectContextHandle);

			if (GameplayEffectSpecHandle.IsValid())
			{
				AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*GameplayEffectSpecHandle.Data.Get(), AbilitySystemComponent.Get());
			}
		}
	}	

	AbilitySystemComponent->DefaultEffectsApplied = true;
}

void ABaseCharacter::OnDeath()
{
	On_Death();
}

