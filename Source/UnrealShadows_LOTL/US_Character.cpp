// Fill out your copyright notice in the Description page of Project Settings.


#include "US_Character.h"

// Sets default values
AUS_Character::AUS_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUS_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

