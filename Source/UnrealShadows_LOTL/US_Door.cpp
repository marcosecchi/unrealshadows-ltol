// Fill out your copyright notice in the Description page of Project Settings.


#include "US_Door.h"

#include "US_Character.h"
#include "Components/BoxComponent.h"

// Sets default values
AUS_Door::AUS_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;
//	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->SetBoxExtent(FVector(400, 400, 250));

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Door Mesh");
	DoorMesh->SetupAttachment(BoxCollision);
	DoorMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/KayKit/DungeonElements/door"));
	if (MeshAsset.Succeeded())
	{
		DoorMesh->SetStaticMesh(MeshAsset.Object);
		const auto HorizontalOffset = DoorMesh->GetStaticMesh()->GetBoundingBox().GetSize().Y / 2;
		DoorMesh->SetRelativeLocation(FVector(0.0f, HorizontalOffset, 0.0f));
	}

	IconMesh = CreateDefaultSubobject<UStaticMeshComponent>("Icon Mesh");
	IconMesh->SetupAttachment(BoxCollision);
	IconMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> IconMeshAsset(TEXT("/Game/KayKit/DungeonElements/coin"));
	if (IconMeshAsset.Succeeded())
	{
		IconMesh->SetStaticMesh(IconMeshAsset.Object);
		IconMesh->SetRelativeLocation(FVector(100.0f, 0.0f, 300.0f));
	}

	bReplicates = true;
}

// Called when the game starts or when spawned
void AUS_Door::BeginPlay()
{
	Super::BeginPlay();

	// Add actor begin overlap event
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AUS_Door::OnBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AUS_Door::OnEndOverlap);
	
	if(IconMesh)
	{
		IconBaseMaterial = IconMesh->GetMaterial(0);
	}
}

void AUS_Door::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACharacter::StaticClass()))
	{
		const auto Character = Cast<ACharacter>(OtherActor);
		if (Character)
		{
			// Print message on screen
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap!"));
			
			if (Execute_CanInteract(this, Character) && IconInteractMaterial)
			{
				IconMesh->SetMaterial(0, IconInteractMaterial);
			}
		}
	}
}

void AUS_Door::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ACharacter::StaticClass()))
	{
		const auto Character = Cast<ACharacter>(OtherActor);
		if (Character)
		{
			// Print message on screen
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End!"));
			
			if(IconBaseMaterial)
				IconMesh->SetMaterial(0, IconBaseMaterial);
		}
		
	}

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

