#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "US_Minion.generated.h"

UCLASS()
class UNREALSHADOWS_LOTL_API AUS_Minion : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Minion AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPawnSensingComponent> PawnSense;

public:
	// Sets default values for this character's properties
	AUS_Minion();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Minion AI")
	float PatrolSpeed = 150.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Minion AI")
	float ChaseSpeed = 450.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Minion AI")
	float PatrolRadius = 50000.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when a pawn has been detected by the pawn sensing component
	UFUNCTION()
	void OnPawnDetected(APawn* Pawn);

	// Called when a pawn has been detected by the pawn sensing component
	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:

	UFUNCTION(BlueprintCallable, Category="Minion AI")
	void SetPatrolSpeed();

	UFUNCTION(BlueprintCallable, Category="Minion AI")
	void SetChaseSpeed();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;
	
	// Called to bind functionality to input
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns PawnSense component **/
	FORCEINLINE UPawnSensingComponent* GetPawnSense() const { return PawnSense; }
};
