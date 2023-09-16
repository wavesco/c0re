#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

class UGameplayTagsManager;

/**
 * MyGameplayTags
 *
 *	Singleton containing native gameplay tags.
 */
struct FDefaultGameplayTags
{
public:

	static const FDefaultGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeTags();

	//Input Tags
	FGameplayTag IT_Move;
	FGameplayTag IT_LookMouse;
	FGameplayTag IT_Jump;
	FGameplayTag IT_Fire;

protected:

	//Registers all of the tags with the GameplayTags Manager
	void AddAllTags(UGameplayTagsManager& Manager);

	//Helper function used by AddAllTags to register a single tag with the GameplayTags Manager
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:

	static FDefaultGameplayTags GameplayTags;
};