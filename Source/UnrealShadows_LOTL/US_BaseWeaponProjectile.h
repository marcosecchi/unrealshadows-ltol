#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "US_BaseWeaponProjectile.generated.h"

UCLASS()
class UNREALSHADOWS_LOTL_API AUS_BaseWeaponProjectile : public AActor
{
	GENERATED_BODY()

	/** The collision component used to detect the character overlapping the pickup. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components",  meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> SphereCollision;

	/** The static mesh used to represent the pickup. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	/** The projectile movement component used to move the weapon. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;

	/** The static mesh used to represent the pickup. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon", meta = (AllowPrivateAccess = "true"))
	float Damage = 1.f;

public:	
	// Sets default values for this actor's properties
	AUS_BaseWeaponProjectile();

protected:
	// Add OnHit handler
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);

public:
	// Getter functions
	FORCEINLINE USphereComponent* GetSphereCollision() const { return SphereCollision; }
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};
