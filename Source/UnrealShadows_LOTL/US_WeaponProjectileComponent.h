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
	TObjectPtr<class UInputMappingContext> WeaponMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ThrowAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile", meta=(AllowPrivateAccess = "true"))
	UAnimMontage* ThrowAnimation;

public:	
	// Sets default values for this component's properties
	UUS_WeaponProjectileComponent();

	// Changes the spawned projectile class
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SetProjectileClass(TSubclassOf<class AUS_BaseWeaponProjectile> NewProjectileClass);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Throw the projectile
	void Throw();

	// Throw the projectile on the server
	UFUNCTION(Server, Reliable)
	void Throw_Server();

	// Call the throw projectile logic from the client
	UFUNCTION(NetMulticast, Unreliable)
	void Throw_Client();
};
