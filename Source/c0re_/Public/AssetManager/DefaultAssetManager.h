#pragma once
 
#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "DefaultAssetManager.generated.h"
 
/**
 * 
 */
UCLASS()
class C0RE__API UDefaultAssetManager : public UAssetManager
{
	GENERATED_BODY()
 
public:
 
	UDefaultAssetManager();
 
	// Returns the AssetManager singleton object.
	static UDefaultAssetManager& Get();
 
protected:
 
	virtual void StartInitialLoading() override;
};