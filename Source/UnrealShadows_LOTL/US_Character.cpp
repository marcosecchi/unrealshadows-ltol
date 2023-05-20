#include "US_Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "US_CharacterStats.h"
#include "Engine/DataTable.h"
#include "US_Interactable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "US_WeaponProjectileComponent.h"

AUS_Character::AUS_Character()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Create the camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create the follow camera and attach it to the camera boom
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Create the noise emitter
	NoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitter"));
	NoiseEmitter->NoiseLifetime = 0.01f;

	Weapon = CreateDefaultSubobject<UUS_WeaponProjectileComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(RootComponent);
	Weapon->SetRelativeLocation(FVector(120.f, 70.f, 0.f));
	/************************** ADDED CODE **************************/
	Weapon->SetIsReplicated(true);
	/************************** END **************************/

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(60.f, 96.0f);

	// Set the skeletal mesh for the character
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -91.f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("/Game/KayKit/Characters/rogue"));
	if (SkeletalMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMeshAsset.Object);
	}

	// Set the character movement properties
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

// Handle the movement input
void AUS_Character::Move(const FInputActionValue& Value)
{
	const auto MovementVector = Value.Get<FVector2D>();
//	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Yellow, FString::Printf(TEXT("MovementVector: %s"), *MovementVector.ToString()));

	// Only add movement if there is a controller possessing this actor
	if (Controller != nullptr)
	{
		const auto Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const auto ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const auto RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

// Handle the look around input
void AUS_Character::Look(const FInputActionValue& Value)
{
	const auto LookAxisVector = Value.Get<FVector2D>();
//	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString::Printf(TEXT("LookAxisVector: %s"), *LookAxisVector.ToString()));

	// Only add look around if there is a controller possessing this actor
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

// Handle the change of speed when the sprint button is pressed
void AUS_Character::SprintStart(const FInputActionValue& Value)
{
		SprintStart_Server();
}

// Handle the change of speed when the sprint button is released
void AUS_Character::SprintEnd(const FInputActionValue& Value)
{
		SprintEnd_Server();
}

// Executes the sprint start action from the server
void AUS_Character::SprintStart_Server_Implementation()
{
	if (GetCharacterStats())
	{
		GetCharacterMovement()->MaxWalkSpeed = GetCharacterStats()->SprintSpeed;
	}
}

// Executes the sprint end action from the server
void AUS_Character::SprintEnd_Server_Implementation()
{
	if (GetCharacterStats())
	{
		GetCharacterMovement()->MaxWalkSpeed = GetCharacterStats()->WalkSpeed;
	}
}

void AUS_Character::Interact(const FInputActionValue& Value)
{
//	GEngine->AddOnScreenDebugMessage(30, 5.f, FColor::Red, TEXT("Interact"));
		Interact_Server();
}

void AUS_Character::Interact_Server_Implementation()
{
	if(InteractableActor)
	{
		IUS_Interactable::Execute_Interact(InteractableActor, this);
	}
}

void AUS_Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString::Printf(TEXT("Tick")));

	if(GetLocalRole() != ROLE_Authority) return;
	
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;

	auto SphereRadius = 50.f;
	auto StartLocation = GetActorLocation() + GetActorForwardVector() * 150.f;
	auto EndLocation = StartLocation + GetActorForwardVector() * 500.f;
	
	auto IsHit = UKismetSystemLibrary::SphereTraceSingle(
	  GetWorld(),
	  StartLocation,
	  EndLocation,
	  SphereRadius,
	  UEngineTypes::ConvertToTraceType(ECC_WorldStatic),
	  false,
	  TArray<AActor*>(),
	  EDrawDebugTrace::ForOneFrame,
	  HitResult,
	  true
	);

	// Check if the hit result implements the US_Interactable interface
	if (IsHit && HitResult.GetActor()->GetClass()->ImplementsInterface(UUS_Interactable::StaticClass()))
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, SphereRadius, 12, FColor::Magenta, false, 1.f);
		InteractableActor = HitResult.GetActor();
	}
	else
	{
		InteractableActor = nullptr;
	}

	// If the character is running, emit noise
	if (GetCharacterMovement()->MaxWalkSpeed == GetCharacterStats()->SprintSpeed)
	{
		auto Noise = 1.f;
		if(GetCharacterStats() && GetCharacterStats()->StealthMultiplier)
		{
			Noise = Noise / GetCharacterStats()->StealthMultiplier;
		}
		NoiseEmitter->MakeNoise(this, Noise, GetActorLocation());
	}
}

void AUS_Character::BeginPlay()
{
	Super::BeginPlay();

	// Add the base mapping context to the player controller only if we are using a PlayerController
	// and if the subsystem is available
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	UpdateCharacterStats(1);
}

// Called to bind functionality to input
void AUS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind the each input action to the corresponding methods
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUS_Character::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUS_Character::Look);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AUS_Character::Interact);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AUS_Character::SprintStart);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AUS_Character::SprintEnd);
	}
}

// Get the character stats from the data table and assign them to the row reference
void AUS_Character::UpdateCharacterStats(int32 CharacterLevel)
{
	auto IsSprinting = false;
	if(GetCharacterStats())
	{
		IsSprinting = GetCharacterMovement()->MaxWalkSpeed == GetCharacterStats()->SprintSpeed;
	}
	
	if(CharacterDataTable)
	{
		// Get all the rows from the data table
		TArray<FUS_CharacterStats*> CharacterStatsRows;
		CharacterDataTable->GetAllRows<FUS_CharacterStats>(TEXT("US_Character"), CharacterStatsRows);

		// Get the row from the data table based on the character level
		if(CharacterStatsRows.Num() > 0)
		{
			const auto NewCharacterLevel = FMath::Clamp(CharacterLevel, 1, CharacterStatsRows.Num());
			CharacterStats = CharacterStatsRows[NewCharacterLevel - 1];

			GetCharacterMovement()->MaxWalkSpeed = GetCharacterStats()->WalkSpeed;
			if(IsSprinting)
			{
				SprintStart_Server();
			}
			// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Level Up: %d"), NewCharacterLevel));
		}
	}
}