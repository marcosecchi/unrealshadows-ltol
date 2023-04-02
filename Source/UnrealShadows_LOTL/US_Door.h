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
	TObjectPtr<UStaticMeshComponent> Mesh;

public:	
	// Sets default values for this actor's properties
	AUS_Door();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
//	virtual void Tick(float DeltaTime) override;

	// Getters for the door components
	
	/** Returns the SpringArmComponent used to connect the Camera to the character Capsule component. */
	FORCEINLINE UBoxComponent* GetBoxCollision() const { return BoxCollision; }

	/** Returns the CameraComponent used as a main camera for the character. */
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }

	// US_InteractableInterface implementation
	
	virtual void Interact_Implementation(ACharacter* CharacterInstigator) override;

	virtual bool CanInteract_Implementation(ACharacter* CharacterInstigator) const override;

	virtual FText GetInteractionText_Implementation(ACharacter* CharacterInstigator) const override;
};
