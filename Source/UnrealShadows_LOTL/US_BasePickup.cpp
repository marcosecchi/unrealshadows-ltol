#include "US_BasePickup.h"

#include "US_Character.h"
#include "Components/SphereComponent.h"

AUS_BasePickup::AUS_BasePickup()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>("Collision");
	RootComponent = SphereCollision;
	SphereCollision->SetGenerateOverlapEvents(true);
	SphereCollision->SetSphereRadius(200.0f);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(SphereCollision);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bReplicates = true;
}

// Called when the game starts or when spawned
void AUS_BasePickup::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AUS_BasePickup::OnBeginOverlap);
}

// Handles the Character overlapping the pickup.
void AUS_BasePickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AUS_Character::StaticClass()))
	{
		const auto Character = Cast<AUS_Character>(OtherActor);
		if (Character)
		{
			Pickup(Character);
		}
	}
}

// Called when the pickup is picked up.
void AUS_BasePickup::Pickup_Implementation(AUS_Character* OwningCharacter)
{
	SetOwner(OwningCharacter);
}

