#include "AssetManager/DefaultAssetManager.h"
#include "GameplayTags/DefaultGameplayTags.h"

UDefaultAssetManager::UDefaultAssetManager()
{

}

UDefaultAssetManager& UDefaultAssetManager::Get()
{
	check(GEngine);

	UDefaultAssetManager* DefaultAssetManager = Cast<UDefaultAssetManager>(GEngine->AssetManager);
	return *DefaultAssetManager;
}

void UDefaultAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	//Load Native Tags
	FDefaultGameplayTags::InitializeNativeTags();
}