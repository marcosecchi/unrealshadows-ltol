#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "US_InteractableInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UUS_InteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class UNREALSHADOWS_LOTL_API IUS_InteractableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void Interact(ACharacter* CharacterInstigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure, Category = "Interaction")
	bool CanInteract(ACharacter* CharacterInstigator) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure, Category = "Interaction")
	FText GetInteractionText(ACharacter* CharacterInstigator) const;
	
};
