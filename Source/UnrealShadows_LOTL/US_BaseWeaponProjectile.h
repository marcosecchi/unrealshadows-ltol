// Fill out your copyright notice in the Description page of Project Settings.

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;

public:	
	// Sets default values for this actor's properties
	AUS_BaseWeaponProjectile();

	/** The static mesh used to represent the pickup. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
	float Damage = 1.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Add OnHit handler
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	FORCEINLINE USphereComponent* GetSphereCollision() const { return SphereCollision; }
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};
