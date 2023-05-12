#include "US_BaseWeaponProjectile.h"

#include "Components/SphereComponent.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AUS_BaseWeaponProjectile::AUS_BaseWeaponProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>("Collision");
	RootComponent = SphereCollision;
	SphereCollision->SetGenerateOverlapEvents(true);
	SphereCollision->SetSphereRadius(50.0f);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(SphereCollision);
	Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Mesh->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("/Game/KayKit/DungeonElements/dagger_common"));
	if (StaticMesh.Succeeded())
	{
		GetMesh()->SetStaticMesh(StaticMesh.Object);
	}

	NoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>("NoiseEmitter");
	NoiseEmitter->NoiseLifetime = 1.f;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->ProjectileGravityScale = 0;
	ProjectileMovement->InitialSpeed = 3000;
	ProjectileMovement->MaxSpeed = 3000;

	bReplicates = true;
}

// Called when the game starts or when spawned
void AUS_BaseWeaponProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUS_BaseWeaponProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

