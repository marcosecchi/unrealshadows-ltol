// Fill out your copyright notice in the Description page of Project Settings.


#include "US_MainMenuPawn.h"

// Sets default values
AUS_MainMenuPawn::AUS_MainMenuPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUS_MainMenuPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUS_MainMenuPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUS_MainMenuPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

