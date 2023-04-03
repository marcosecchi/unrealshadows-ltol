// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "US_InteractableInterface.h"
#include "GameFramework/Actor.h"
#include "US_Door.generated.h"

UCLASS()
class UNREALSHADOWS_LOTL_API AUS_Door : public AActor, public IUS_InteractableInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components",  meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> DoorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> IconMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Materials", meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* IconInteractMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Materials", meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* IconBaseMaterial;

public:	
	// Sets default values for this actor's properties
	AUS_Door();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
//	virtual void Tick(float DeltaTime) override;

	// Getters for the door components

	/** Returns the BoxCollision used as a trigger for the character. */
	FORCEINLINE UBoxComponent* GetBoxCollision() const { return BoxCollision; }

	/** Returns the StaticMeshComponent used to display the door. */
	FORCEINLINE UStaticMeshComponent* GetDoorMesh() const { return DoorMesh; }

	/** Returns the StaticMeshComponent used to display the character interaction result. */
	FORCEINLINE UStaticMeshComponent* GetIconMesh() const { return IconMesh; }

	// US_InteractableInterface implementation
	
	virtual void Interact_Implementation(ACharacter* CharacterInstigator) override;

	virtual bool CanInteract_Implementation(ACharacter* CharacterInstigator) const override;

	virtual FText GetInteractionText_Implementation(ACharacter* CharacterInstigator) const override;
};
