#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "US_CharacterSkins.generated.h"

USTRUCT(BlueprintType)
struct UNREALSHADOWS_LOTL_API FUS_CharacterSkins : public FTableRowBase
{
	GENERATED_BODY()

	// The Skin material
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInterface *Material4;

	// The garment material
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInterface *Material0;

	// The hair material
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInterface *Material1;

	// The decorations material
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInterface *Material2;
};
