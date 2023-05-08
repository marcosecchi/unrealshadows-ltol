#include "US_Minion.h" 
#include "US_Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AUS_Minion::AUS_Minion()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	PawnSense = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSense"));
	PawnSense->SensingInterval = .8f;
	PawnSense->SetPeripheralVisionAngle(45.f);
	PawnSense->SightRadius = 1500.f;
	PawnSense->HearingThreshold = 400.f;
	PawnSense->LOSHearingThreshold = 800.f;
	
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
}

// Called when the game starts or when spawned
void AUS_Minion::BeginPlay()
{
	Super::BeginPlay();
//	GetPawnSense()->OnSeePawn.AddDynamic(this, &AUS_Minion::OnPawnDetected);
	SetPatrolSpeed();
}

void AUS_Minion::SetPatrolSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = PatrolSpeed;
}

void AUS_Minion::SetChaseSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
}

void AUS_Minion::OnPawnDetected(APawn* Pawn)
{
	// Checks if the pawn is a US_Character
	if (!Pawn->IsA<AUS_Character>()) return;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Character detected!"));
	
	// If the AI character is not already in the chase state
	if (GetCharacterMovement()->MaxWalkSpeed != ChaseSpeed)
	{
		// Set the AI character's destination to the player's location
		UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), Pawn);

		// Displays the AI character's destination
		DrawDebugSphere(GetWorld(), Pawn->GetActorLocation(), 25.f, 12, FColor::Red, true, 10.f, 0, 2.f);
	}
}

void AUS_Minion::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	// Checks if the pawn is a US_Character
	if (!OtherActor->IsA<AUS_Character>()) return;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Character captured!"));
}

// Called every frame
void AUS_Minion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUS_Minion::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	this->OnActorBeginOverlap.AddDynamic(this, &AUS_Minion::OnBeginOverlap);
	GetPawnSense()->OnSeePawn.AddDynamic(this, &AUS_Minion::OnPawnDetected);
}

// Called to bind functionality to input
//void AUS_Minion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//}

