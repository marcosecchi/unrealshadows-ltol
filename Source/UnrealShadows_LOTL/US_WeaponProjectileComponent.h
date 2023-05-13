// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "US_WeaponProjectileComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALSHADOWS_LOTL_API UUS_WeaponProjectileComponent : public USceneComponent
{
	GENERATED_BODY()

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile",  meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AUS_BaseWeaponProjectile> ProjectileClass;

	// Declare the input mapping context for the basic actions (movement, interaction, etc.)

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* WeaponMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	class UInputAction* ThrowAction;

public:	
	// Sets default values for this component's properties
	UUS_WeaponProjectileComponent();

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SetProjectileClass(TSubclassOf<class AUS_BaseWeaponProjectile> NewProjectileClass);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void Throw();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
