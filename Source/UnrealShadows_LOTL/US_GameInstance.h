// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "US_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSHADOWS_LOTL_API UUS_GameInstance : public UGameInstance
{
	GENERATED_BODY()

	/********************************************* ADD THIS *********************************************/
public:
	// the player name
	UPROPERTY(BlueprintReadWrite)
	FString PlayerName;

	
	UPROPERTY(BlueprintReadWrite)
	FString PlayerSkinAssetPath;

	UPROPERTY(BlueprintReadWrite)
	FString PlayerMaterial0AssetPath;

	UPROPERTY(BlueprintReadWrite)
	FString PlayerMaterial1AssetPath;

	UPROPERTY(BlueprintReadWrite)
	FString PlayerMaterial2AssetPath;
	
	/********************************************* END *********************************************/	
};
