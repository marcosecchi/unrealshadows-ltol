#include "US_WeaponProjectileComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "US_BaseWeaponProjectile.h"
#include "US_Character.h"

UUS_WeaponProjectileComponent::UUS_WeaponProjectileComponent()
{
	ProjectileClass = AUS_BaseWeaponProjectile::StaticClass();
}

void UUS_WeaponProjectileComponent::BeginPlay()
{
	Super::BeginPlay();

	// Add the base mapping context to the player controller only if we are using a PlayerController
	const AUS_Character* Character = Cast<AUS_Character>(GetOwner());
	if(!Character) return;
	
	if (const APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(WeaponMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Triggered, this, &UUS_WeaponProjectileComponent::Throw);
		}
	}
}

void UUS_WeaponProjectileComponent::Throw()
{
	Throw_Server();
}

void UUS_WeaponProjectileComponent:: Throw_Server_Implementation()
{
	// Spawn the projectile, setting its owner and instigator as the spawning character
	if (ProjectileClass)
	{
		// Call the client side method to play the animation
		Throw_Client();
		// Delay the spawn of the projectile to match the animation
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			const auto Character = Cast<AUS_Character>(GetOwner());
			const auto ProjectileSpawnLocation = GetComponentLocation();
			const auto ProjectileSpawnRotation = GetComponentRotation();
			auto ProjectileSpawnParams = FActorSpawnParameters();
			ProjectileSpawnParams.Owner = GetOwner();
			ProjectileSpawnParams.Instigator = Character;

			GetWorld()->SpawnActor<AUS_BaseWeaponProjectile>(ProjectileClass, ProjectileSpawnLocation, ProjectileSpawnRotation, ProjectileSpawnParams);
		}, .4f, false);
	}
}

void  UUS_WeaponProjectileComponent::Throw_Client_Implementation()
{
	// Play the animation on the client side
	const auto Character = Cast<AUS_Character>(GetOwner());
	if (ThrowAnimation != nullptr)
	{
		if (const auto AnimInstance = Character->GetMesh()->GetAnimInstance(); AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(ThrowAnimation, 1.f);
		}
	}	
}

void UUS_WeaponProjectileComponent::SetProjectileClass(TSubclassOf<AUS_BaseWeaponProjectile> NewProjectileClass)
{
	// Assign the new projectile class
	ProjectileClass = NewProjectileClass;
}
