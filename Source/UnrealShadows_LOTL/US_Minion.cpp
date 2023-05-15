#include "US_Minion.h" 

#include "AIController.h"
#include "NavigationSystem.h"
#include "US_Character.h"
#include "US_GameMode.h"
/************************** ADD THIS **************************/
#include "US_BasePickup.h"
/*************************************************************/
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/SphereComponent.h"

AUS_Minion::AUS_Minion()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAIController::StaticClass();

	PawnSense = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSense"));
	PawnSense->SensingInterval = .8f;
	PawnSense->SetPeripheralVisionAngle(45.f);
	PawnSense->SightRadius = 1500.f;
	PawnSense->HearingThreshold = 400.f;
	PawnSense->LOSHearingThreshold = 800.f;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetSphereRadius(100);
	Collision->SetupAttachment(RootComponent);

	GetCapsuleComponent()->InitCapsuleSize(60.f, 96.0f);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	
	// Set the skeletal mesh for the character
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -91.f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("/Game/KayKit/Skeletons/skeleton_minion"));
	if (SkeletalMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMeshAsset.Object);
	}

	// Set the character movement properties
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	/*************************** ADD THIS ***************************/
	static ConstructorHelpers::FClassFinder<AUS_BasePickup> SpawnedPickupAsset(TEXT("/Game/Blueprints/PB_GoldCoinPickup"));
	if (SpawnedPickupAsset.Succeeded())
	{
		SpawnedPickup = SpawnedPickupAsset.Class;
	}
/******************************************************************/
}

// Called when the game starts or when spawned
void AUS_Minion::BeginPlay()
{
	Super::BeginPlay();
	SetNextPatrolLocation();
}

void AUS_Minion::SetNextPatrolLocation()
{
	GetCharacterMovement()->MaxWalkSpeed = PatrolSpeed;

	const auto LocationFound = UNavigationSystemV1::K2_GetRandomReachablePointInRadius(
		this, GetActorLocation(), PatrolLocation, PatrolRadius);
	if(LocationFound)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), PatrolLocation);
	}
}

void AUS_Minion::Chase(APawn* Pawn)
{
	GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
	// Set the AI character's destination to the player's location
	UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), Pawn);

	// Displays the AI character's destination
	DrawDebugSphere(GetWorld(), Pawn->GetActorLocation(), 25.f, 12, FColor::Red, true, 10.f, 0, 2.f);

	// Get the game mode and alert the minions
	if(const auto GameMode = Cast<AUS_GameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->AlertMinions(this, Pawn->GetActorLocation(), AlertRadius);
	}
}

void AUS_Minion::OnPawnDetected(APawn* Pawn)
{
	// Checks if the pawn is a US_Character
	if (!Pawn->IsA<AUS_Character>()) return;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Character detected!"));
	
	// If the AI character is not already in the chase state
	if (GetCharacterMovement()->MaxWalkSpeed != ChaseSpeed)
	{
		Chase(Pawn);
	}
}

void AUS_Minion::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Noise detected!"));
	GoToLocation(Location);
}

void AUS_Minion::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	// Checks if the pawn is a US_Character
	if (!OtherActor->IsA<AUS_Character>()) return;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Character captured!"));
}

/************************************** ADD THIS ****************************************/
void AUS_Minion::OnDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
	AActor* DamageCauser)
{
	// Checks if the pawn is a US_Character
	//	if (!DamageCauser->IsA<AUS_Character>()) return;
	//	Chase(DamageCauser);
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Character damaged!"));
	Health -= Damage;
	if(Health > 0) return;

	// Spawn SpawnedPickup at character location
	if(SpawnedPickup)
	{
		FActorSpawnParameters SpawnParams;
		GetWorld()->SpawnActor<AUS_BasePickup>(SpawnedPickup, GetActorLocation(), GetActorRotation(), SpawnParams);
	}
	Destroy();


	
}

/****************************************************************************************/

void AUS_Minion::GoToLocation(const FVector& Location)
{
	PatrolLocation = Location;
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), PatrolLocation);
}

void AUS_Minion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GetMovementComponent()->GetMaxSpeed() == ChaseSpeed) return;

	if((GetActorLocation() - PatrolLocation).Size() < 500.f)
	{
		SetNextPatrolLocation();
	}
}

void AUS_Minion::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	/************************************** ADD THIS ****************************************/
	this->OnTakeAnyDamage.AddDynamic(this, &AUS_Minion::OnDamage);
	/******************************************************************************/
	this->OnActorBeginOverlap.AddDynamic(this, &AUS_Minion::OnBeginOverlap);
	GetPawnSense()->OnSeePawn.AddDynamic(this, &AUS_Minion::OnPawnDetected);
	GetPawnSense()->OnHearNoise.AddDynamic(this, &AUS_Minion::OnHearNoise);
}
