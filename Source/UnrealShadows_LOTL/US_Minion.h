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

	// The regular speed of the character
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Minion AI")
	float PatrolSpeed = 150.0f;

	// The chase speed of the character
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Minion AI")
	float ChaseSpeed = 350.0f;

	// The distance used to find the next patrol location
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Minion AI")
	float PatrolRadius = 50000.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when a pawn has been detected by the pawn sensing component
	UFUNCTION()
	void OnPawnDetected(APawn* Pawn);

	/** Called when a noise is heard by the pawn sensing component */
	UFUNCTION()
	void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);

	// Called when a pawn has been detected by the pawn sensing component
	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:

	// Look for another location to reach
	UFUNCTION(BlueprintCallable, Category="Minion AI")
	void SetNextPatrolLocation();

	// Start seeking a character
	UFUNCTION(BlueprintCallable, Category="Minion AI")
	void Chase(APawn* Pawn);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind callbacks
	virtual void PostInitializeComponents() override;

	/** Returns PawnSense component **/
	FORCEINLINE UPawnSensingComponent* GetPawnSense() const { return PawnSense; }

	/** Returns PawnSense component **/
	FORCEINLINE USphereComponent* GetCollision() const { return Collision; }
};
