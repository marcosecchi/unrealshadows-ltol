#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "US_PlayerState.generated.h"

// Event handler for experience points changed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnXpChanged, int32, NewXp);
// Event handler for level experience changed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterLevelUp, int32, NewLevelXp);
/************************************* ADD THIS *************************************/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkinChanged, int32, NewSkinIndex);
/************************************* END *************************************/

UCLASS()
class UNREALSHADOWS_LOTL_API AUS_PlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	
	/** The experience points of the player. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, ReplicatedUsing="OnRep_Xp", Category = "Experience")
	int Xp = 0;

	/** The experience points gained so far by the player. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, ReplicatedUsing="OnRep_CharacterLevelUp", Category = "Experience")
	int CharacterLevel = 1;
	
	// Called whenever an Xp replication occurs
	UFUNCTION()
	void OnRep_Xp(int32 OldValue) const;

	// Called whenever a CharacterLevel replication occurs
	UFUNCTION()
	void OnRep_CharacterLevelUp(int32 OldValue) const;

	/************************************* ADD THIS *************************************/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, ReplicatedUsing="OnRep_SkinChanged", Category = "Skin")
	int SkinIndex = 0;

	UFUNCTION()
	void OnRep_SkinChanged(int32 OldValue) const;
	/************************************* END *************************************/

public:

	/************************************* ADD THIS *************************************/
	UFUNCTION(BlueprintCallable, Category="Experience")
	void SetSkinIndex(int32 Value);

	UFUNCTION(BlueprintCallable, Category="Experience")
	int32 GetSkinIndex();
	/************************************* END *************************************/

	/** Adds experience points to the player. */
	UFUNCTION(BlueprintCallable, Category="Experience")
	void AddXp(int32 Value);

	// Used to broadcast the experience points changed event
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnXpChanged OnXpChanged;

	// Used to broadcast the character level up event
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCharacterLevelUp OnCharacterLevelUp;

	/************************************* ADD THIS *************************************/
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnSkinChanged OnSkinChanged;
	/************************************* END *************************************/

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
