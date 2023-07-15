#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "US_MainMenuPawn.generated.h"

UCLASS()
class UNREALSHADOWS_LOTL_API AUS_MainMenuPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Arrow", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UArrowComponent> Arrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Mesh;

	/** A reference to the data table containing the character stats. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Data", meta = (AllowPrivateAccess = "true"))
	class UDataTable* CharacterSkinDataTable;

	/** The character skin, retrieved from the data table. */
	struct FUS_CharacterSkins* CharacterSkin;

public:
	// Sets default values for this pawn's properties
	AUS_MainMenuPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void RandomizeCharacterSkin();

public:

	// Getter for the character skins
	FORCEINLINE FUS_CharacterSkins* GetCharacterSkins() const { return CharacterSkin; }

	// Getters for the private components
	FORCEINLINE UArrowComponent* GetArrow() const { return Arrow; }
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }
	FORCEINLINE USkeletalMeshComponent* GetMesh() const { return Mesh; }
};
