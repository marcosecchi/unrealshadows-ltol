#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "US_Minion.generated.h"

UCLASS()
class UNREALSHADOWS_LOTL_API AUS_Minion : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Minion Perception", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPawnSensingComponent> PawnSense;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Minion Perception", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> Collision;

	UPROPERTY()
	FVector PatrolLocation;

public:
	// Sets default values for this character's properties
	AUS_Minion();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Minion AI")
	float PatrolSpeed = 150.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Minion AI")
	float ChaseSpeed = 350.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Minion AI")
	float PatrolRadius = 50000.0f;

	/***************************** ADD THIS *****************************/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Pickup")
	TSubclassOf<class AUS_BasePickup> SpawnedPickup;
	/***********************************************************************/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when a pawn has been detected by the pawn sensing component
	UFUNCTION()
	void OnPawnDetected(APawn* Pawn);

	/***************************** ADD THIS *****************************/
	/** Called when a noise is heard by the pawn sensing component */
	UFUNCTION()
	void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);
	/***********************************************************************/

	/***************************** ADD THIS *****************************/
	UFUNCTION()
	void OnDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
	/***********************************************************************/

	// Called when a pawn has been detected by the pawn sensing component
	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	/***************************** ADD THIS *****************************/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Health")
	float Health = 5.f;
	/**********************************************************/

public:

	UFUNCTION(BlueprintCallable, Category="Minion AI")
	void SetNextPatrolLocation();

	UFUNCTION(BlueprintCallable, Category="Minion AI")
	void Chase(APawn* Pawn);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

	/** Returns PawnSense component **/
	FORCEINLINE UPawnSensingComponent* GetPawnSense() const { return PawnSense; }

	/** Returns PawnSense component **/
	FORCEINLINE USphereComponent* GetCollision() const { return Collision; }
};