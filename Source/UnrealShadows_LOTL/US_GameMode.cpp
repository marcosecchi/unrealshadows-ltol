
#include "US_GameMode.h"

#include "US_GameState.h"
#include "US_PlayerController.h"
#include "US_PlayerState.h"
/************************************** ADD THIS ****************************************/
#include "US_Minion.h"
#include "Kismet/GameplayStatics.h"
/****************************************************************************************/
#include "UObject/ConstructorHelpers.h"

AUS_GameMode::AUS_GameMode()
{
	// Declare all the Gameplay Framework classes we want to use
	GameStateClass = AUS_GameState::StaticClass();
	PlayerStateClass = AUS_PlayerState::StaticClass();
	PlayerControllerClass = AUS_PlayerController::StaticClass();
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Character"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AUS_GameMode::AlertMinions(AActor* AlertInstigator, const FVector& Location, const float Radius)
{
	// Get all actors of type AUS_Minion
	TArray<AActor*> Minions;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUS_Minion::StaticClass(), Minions);

	// Loop through all minions
	for (const auto Minion : Minions)
	{
		if(AlertInstigator == Minion) continue; 
		// Get the distance between the alerting minion and the current minion
		// If the distance is less than the radius
		if (const auto Distance = FVector::Distance(AlertInstigator->GetActorLocation(), Minion->GetActorLocation()); Distance < Radius)
		{
			// If the actor is a minion
			if (const auto MinionCharacter = Cast<AUS_Minion>(Minion))
			{
				// Set the minion's patrol location to the alerting minion's location
				MinionCharacter->GoToLocation(Location);
			}
		}
	}
}
