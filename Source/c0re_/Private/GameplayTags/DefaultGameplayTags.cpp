#include "GameplayTags/DefaultGameplayTags.h"
#include "GameplayTags.h"
#include "GameplayTagsManager.h"
#include "Engine/EngineTypes.h"

FDefaultGameplayTags FDefaultGameplayTags::GameplayTags;

void FDefaultGameplayTags::InitializeNativeTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();

	GameplayTags.AddAllTags(GameplayTagsManager);

	GameplayTagsManager.DoneAddingNativeTags();
}

void FDefaultGameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
	AddTag(IT_Move, "InputTag.Move", "Move input.");
	AddTag(IT_LookMouse, "InputTag.Look.Mouse", "Look (mouse) input.");
	AddTag(IT_Jump, "InputTag.Jump", "Jump input");
	AddTag(IT_Fire, "InputTag.Fire", "Fire input.");
}

void FDefaultGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}