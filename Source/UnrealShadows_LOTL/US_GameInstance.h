#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "US_GameInstance.generated.h"

UCLASS()
class UNREALSHADOWS_LOTL_API UUS_GameInstance : public UGameInstance
{
	GENERATED_BODY()

	/********************************************* ADD THIS *********************************************/
public:
	// the player name
	UPROPERTY(BlueprintReadWrite)
	int32 SkinIndex;

	
	/********************************************* END *********************************************/	
};
