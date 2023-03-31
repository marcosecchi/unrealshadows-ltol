// Fill out your copyright notice in the Description page of Project Settings.


#include "US_GameMode.h"

#include "US_GameState.h"
#include "US_PlayerController.h"
#include "US_PlayerState.h"
#include "US_Character.h"
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
