#include "US_PlayerState.h"

#include "US_Character.h"
#include "US_CharacterStats.h"
#include "Net/UnrealNetwork.h"

void AUS_PlayerState::AddXp(const int32 Value)
{
	Xp += Value;
	OnXpChanged.Broadcast(Xp);

	 GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Yellow, FString::Printf(TEXT("Total Xp: %d"), Value));

	if (const auto Character = Cast<AUS_Character>(GetPawn()))
	{
		if(Character->GetCharacterStats()->NextLevelXp < Xp)
		{
			GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Red, TEXT("Level Up!"));
			
			CharacterLevel++;
	OnCharacterLevelUp.Broadcast(CharacterLevel);
			Character->UpdateCharacterStats(CharacterLevel);
		}
	}
}

void AUS_PlayerState::OnRep_Xp(int32 OldValue) const
{
	OnXpChanged.Broadcast(Xp);
}

void AUS_PlayerState::OnRep_CharacterLevelUp(int32 OldValue) const
{
	OnCharacterLevelUp.Broadcast(CharacterLevel);
}

/**
 * Called to get the list of replicated properties
 * @param OutLifetimeProps - List of replicated properties
 */
void AUS_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AUS_PlayerState, Xp, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AUS_PlayerState, CharacterLevel, COND_OwnerOnly);
}