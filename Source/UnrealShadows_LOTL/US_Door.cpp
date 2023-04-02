// Fill out your copyright notice in the Description page of Project Settings.


#include "US_Door.h"

#include "Components/BoxComponent.h"

// Sets default values
AUS_Door::AUS_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollision->SetBoxExtent(FVector(400, 400, 250));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(BoxCollision);
	Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/KayKit/DungeonElements/door"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetStaticMesh(MeshAsset.Object);
		const auto Offset = Mesh->GetStaticMesh()->GetBoundingBox().GetSize().Y / 2;
		Mesh->SetRelativeLocation(FVector(0.0f, -Offset, 0.0f));
	}

	bReplicates = true;
}

// Called when the game starts or when spawned
void AUS_Door::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
//void AUS_Door::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);

//}

void AUS_Door::Interact_Implementation(ACharacter* CharacterInstigator)
{
	IUS_InteractableInterface::Interact_Implementation(CharacterInstigator);
}

bool AUS_Door::CanInteract_Implementation(ACharacter* CharacterInstigator) const
{
	return true;
}

FText AUS_Door::GetInteractionText_Implementation(ACharacter* CharacterInstigator) const
{
	return FText::FromString("Door Opened!");
}

