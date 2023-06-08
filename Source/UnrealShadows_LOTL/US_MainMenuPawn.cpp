// Fill out your copyright notice in the Description page of Project Settings.


#include "US_MainMenuPawn.h"

#include "US_CharacterSkins.h"
#include "US_GameInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
AUS_MainMenuPawn::AUS_MainMenuPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	RootComponent = Arrow;

	// Create the follow camera and attach it to the camera boom
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(450.f, 90.f, 160.f));
	Camera->SetRelativeRotation(FRotator(-10.f, 180.f, 0.f));

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("/Game/KayKit/Characters/rogue"));
	if (SkeletalMeshAsset.Succeeded())
	{
		Mesh->SetSkeletalMesh(SkeletalMeshAsset.Object);
	}
	Mesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
//	static ConstructorHelpers::FObjectFinder<UAnimationAsset> AnimationAsset(TEXT("/Game/KayKit/Characters/RogueAnimation/rogue_Idle.rogue_Idle"));
//	if (AnimationAsset.Succeeded())
//	{
//		Mesh->SetAnimation(AnimationAsset.Object);
//	}
	// TODO: Assign Animation
}

// Called when the game starts or when spawned
void AUS_MainMenuPawn::BeginPlay()
{
	Super::BeginPlay();

	if(IsLocallyControlled())
	{
		RandomizeCharacterSkin();
	}
}

void AUS_MainMenuPawn::RandomizeCharacterSkin()
{
	if(CharacterSkinDataTable)
	{
		// Get all the rows from the data table
		TArray<FUS_CharacterSkins*> CharacterSkinsRows;
		CharacterSkinDataTable->GetAllRows<FUS_CharacterSkins>(TEXT("US_Character"), CharacterSkinsRows);

		// Get the row from the data table
		if(CharacterSkinsRows.Num() > 0)
		{
			const auto NewIndex = FMath::RandRange(0, CharacterSkinsRows.Num() - 1);
			CharacterSkin = CharacterSkinsRows [NewIndex];

			Mesh->SetMaterial(4, CharacterSkinsRows[NewIndex]->Material4);
			Mesh->SetMaterial(0, CharacterSkinsRows[NewIndex]->Material0);
			Mesh->SetMaterial(1, CharacterSkinsRows[NewIndex]->Material1);
			Mesh->SetMaterial(2, CharacterSkinsRows[NewIndex]->Material2);

			// Get the GameInstance
			if (const auto GameInstance = Cast<UUS_GameInstance>(GetGameInstance()))
			{
				GameInstance->SkinIndex = NewIndex;
			}
		}
	}

}

