#include "US_PlayerState.h"

#include "US_Character.h"
#include "US_CharacterStats.h"
#include "Net/UnrealNetwork.h"

int32 AUS_PlayerState::GetXp() const
{
	return Xp;
}

void AUS_PlayerState::AddXp(const int32 Value)
{
	Xp += Value;
	OnXpChanged.Broadcast(this, Xp);

	const auto Character = Cast<AUS_Character>(GetPawn());
	if (Character)
	{
		if(Character->GetCharacterStats()->NextLevelXp < Xp)
		{
			LevelXp++;
			OnLevelXpUp.Broadcast(this, LevelXp);
		}
	}
}

int32 AUS_PlayerState::GetLevelXp() const
{
	return LevelXp;
}

void AUS_PlayerState::OnRep_Xp(int32 OldXp)
{
	OnXpChanged.Broadcast(this, Xp);
}

void AUS_PlayerState::OnRep_LevelXpUp(int32 OldLevelXp)
{
	OnLevelXpUp.Broadcast(this, LevelXp);
}

/**
 * Called to get the list of replicated properties
 * @param OutLifetimeProps - List of replicated properties
 */
void AUS_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUS_PlayerState, Xp);
	DOREPLIFETIME(AUS_PlayerState, LevelXp);
}