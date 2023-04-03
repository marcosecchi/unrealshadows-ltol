#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "US_BasePickup.generated.h"

UCLASS()
class UNREALSHADOWS_LOTL_API AUS_BasePickup : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components",  meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> SphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

public:	
	// Sets default values for this actor's properties
	AUS_BasePickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Pickup", meta=(DisplayName="Pickup"))
	void Pickup(AActor* NewOwner);

	void Pickup_Implementation(AActor* NewOwner);


public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	/** Returns the BoxCollision used as a trigger for the character. */
	FORCEINLINE USphereComponent* GetSphereCollision() const { return SphereCollision; }

	/** Returns the Static Mesh. */
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }

};
