#include "US_BasePickup.h"

#include "US_Character.h"
#include "Components/SphereComponent.h"

AUS_BasePickup::AUS_BasePickup()
{
//	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>("Collision");
	RootComponent = SphereCollision;
	SphereCollision->SetGenerateOverlapEvents(true);
	SphereCollision->SetSphereRadius(200.0f);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(SphereCollision);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AUS_BasePickup::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AUS_BasePickup::OnBeginOverlap);
}

void AUS_BasePickup::Pickup_Implementation(AActor* NewOwner)
{
	SetOwner(NewOwner);
}

void AUS_BasePickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
//	return;
	if (OtherActor->IsA(AUS_Character::StaticClass()))
	{
		const auto Character = Cast<AUS_Character>(OtherActor);
		if (Character)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Pickup!"));
			Pickup(OtherActor);
		}
	}

}

// Called every frame
//void ABasePickup::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);

//}

