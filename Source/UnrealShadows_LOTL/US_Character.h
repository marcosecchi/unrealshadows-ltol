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

	// Declare the input mapping context for the basic actions (movement, interaction, etc.)

	/** The default input mapping context for the character: handles movement, look around and interaction. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	// Declare the basic input actions (movement, interaction, etc.)

	/** The input action for moving the character. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** The input action for looking around with the character. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** The input action for sprinting with the character. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	/** The input action for interacting with the environment. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	/********************** ADD **********************/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Data", meta = (AllowPrivateAccess = "true"))
	class UDataTable* CharacterDataTable;

	struct FUS_CharacterStats* CharacterStats;
	/********************** END ADD **********************/
	
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

	/** The function called when the character interacts with the environment. */
	void Interact(const FInputActionValue& Value);

public:	
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Getters for the camera components
	
	/** Returns the SpringArmComponent used to connect the Camera to the character Capsule component. */
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns the CameraComponent used as a main camera for the character. */
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/********************** ADD **********************/
	/** Returns the default input mapping context for the character. */
	FORCEINLINE FUS_CharacterStats* GetCharacterStats() const { return CharacterStats; }
	/********************** END **********************/

};
