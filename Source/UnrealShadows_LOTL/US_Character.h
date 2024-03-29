#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "US_Character.generated.h"

UCLASS()
class UNREALSHADOWS_LOTL_API AUS_Character : public ACharacter
{
	GENERATED_BODY()

	// Camera component declaration with the corresponding SpringArm

	/** Used to connect the Camera to the character Capsule component. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	/** Used as a main camera for the character: it is connected through a SpringArmComponent. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

	// Other components declaration

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stealth", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPawnNoiseEmitterComponent> NoiseEmitter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UUS_WeaponProjectileComponent> Weapon;
	
	// Declare the input mapping context for the basic actions (movement, interaction, etc.)

	/** The default input mapping context for the character: handles movement, look around and interaction. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	// Declare the basic input actions (movement, interaction, etc.)

	/** The input action for moving the character. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	/** The input action for looking around with the character. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	/** The input action for sprinting with the character. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SprintAction;

	/** The input action for interacting with the environment. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InteractAction;
	/** A reference to the data table containing the character stats. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Data", meta = (AllowPrivateAccess = "true"))
	class UDataTable* CharacterDataTable;

	/** The character stats, retrieved from the data table. */
	struct FUS_CharacterStats* CharacterStats;

	UPROPERTY()
	AActor* InteractableActor;

	/** A reference to the data table containing the character stats. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Data", meta = (AllowPrivateAccess = "true"))
	UDataTable* CharacterSkinDataTable;

	/** The character skin, retrieved from the data table. */
	struct FUS_CharacterSkins* CharacterSkin;
	
public:
	AUS_Character();

protected:
	virtual void BeginPlay() override;

	// Declare the basic actions (movement, interaction, etc.)

	/** The function called when the character moves. */
	void Move(const struct FInputActionValue& Value);

	/** The function called when the character looks around. */
	void Look(const FInputActionValue& Value);

	/** The function called when the character starts sprinting. */
	void SprintStart(const FInputActionValue& Value);

	/** The function called when the character stops sprinting. */
	void SprintEnd(const FInputActionValue& Value);

	/** The function called on the server when the character starts sprinting. */
	UFUNCTION(Server, Reliable)
	void SprintStart_Server();

	/** The function called on the server when the character stops sprinting. */
	UFUNCTION(Server, Reliable)
	void SprintEnd_Server();

	/** The function called on the client when the character starts sprinting. */
	UFUNCTION(NetMulticast, Reliable)
	void SprintStart_Client();

	/** The function called on the client when the character stops sprinting. */
	UFUNCTION(NetMulticast, Reliable)
	void SprintEnd_Client();
	
	/** The function called when the character interacts with the environment. */
	void Interact(const FInputActionValue& Value);

	/** The function called on the server when the character interacts with the environment. */
	UFUNCTION(Server, Reliable)
	void Interact_Server();

	// The index used to get the character skin from the data table
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, ReplicatedUsing="OnRep_SkinChanged", Category = "Skin")
	int32 SkinIndex = 0;

	// The function called when the character changes skin index
	UFUNCTION()
	void OnRep_SkinChanged(int32 OldValue);

	// The function called on the server when the character changes skin
	UFUNCTION(Server, Reliable)
	void SetSkinIndex_Server(int32 Value);

	// Updates the character skin
	UFUNCTION()
	void UpdateCharacterSkin();

public:	
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/** Updates the character stats based on the level. */
	void UpdateCharacterStats(int32 CharacterLevel);

	// Getters for the camera components
	
	/** Returns the SpringArmComponent used to connect the Camera to the character Capsule component. */
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns the CameraComponent used as a main camera for the character. */
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// Getter for the character statistics based on the level
	FORCEINLINE FUS_CharacterStats* GetCharacterStats() const { return CharacterStats; }

	// Getter for the weapon component
	FORCEINLINE UUS_WeaponProjectileComponent* GetWeapon() const { return Weapon; }

	// Getter for the character skins
	FORCEINLINE FUS_CharacterSkins* GetCharacterSkins() const { return CharacterSkin; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
