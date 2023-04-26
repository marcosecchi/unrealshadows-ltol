 #pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "US_PlayerState.generated.h"

// Event handler for experience points changed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnXpChanged, AUS_PlayerState*, PlayerState, int32, NewXp);
// Event handler for level experience changed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterLevelUp, AUS_PlayerState*, PlayerState, int32, NewLevelXp);

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

	UFUNCTION()
	void OnRep_Xp(int32 OldValue);

	UFUNCTION()
	void OnRep_CharacterLevelUp(int32 OldValue);


public:

	/** Getter for the experience points of the player. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Experience")
	int32 GetXp() const;

	/** Adds experience points to the player. */
	UFUNCTION(BlueprintCallable, Category="Experience")
	void AddXp(int32 Value);
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnXpChanged OnXpChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCharacterLevelUp OnCharacterLevelUp;

	FORCEINLINE int32 GetCharacterLevel() const { return CharacterLevel; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
