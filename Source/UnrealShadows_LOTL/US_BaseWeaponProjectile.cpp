#include "US_BaseWeaponProjectile.h"

#include "US_Character.h"
#include "US_CharacterStats.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/ProjectileMovementComponent.h"

AUS_BaseWeaponProjectile::AUS_BaseWeaponProjectile()
{
	// Initialize the collision sphere
	SphereCollision = CreateDefaultSubobject<USphereComponent>("Collision");
	SphereCollision->SetGenerateOverlapEvents(true);
	SphereCollision->SetSphereRadius(10.0f);
	SphereCollision->BodyInstance.SetCollisionProfileName("BlockAll");
	SphereCollision->OnComponentHit.AddDynamic(this, &AUS_BaseWeaponProjectile::OnHit);
	
	RootComponent = SphereCollision;

	// Initialize the mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Mesh->SetRelativeLocation(FVector(-40.f, 0.f, 0.f));
	Mesh->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("/Game/KayKit/DungeonElements/dagger_common"));
	if (StaticMesh.Succeeded())
	{
		GetMesh()->SetStaticMesh(StaticMesh.Object);
	}

	// Initialize the projectile movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->UpdatedComponent = SphereCollision;
	ProjectileMovement->ProjectileGravityScale = 0;
	ProjectileMovement->InitialSpeed = 3000;
	ProjectileMovement->MaxSpeed = 3000;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	// MAke the projectile replicate
	bReplicates = true;
}

void AUS_BaseWeaponProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto ComputedDamage = Damage;
	if (const auto Character = Cast<AUS_Character>(GetInstigator()))
	{
		ComputedDamage *= Character->GetCharacterStats()->DamageMultiplier;
	}
	GEngine->AddOnScreenDebugMessage(345, 5.f, FColor::Red, FString::Printf(TEXT("Damage: %f"), ComputedDamage));
	if (OtherActor && OtherActor != this)
	{
		const FDamageEvent Event(UDamageType::StaticClass());
		OtherActor->TakeDamage(ComputedDamage, Event, this->GetInstigatorController(), this);
	}
	Destroy();
}

