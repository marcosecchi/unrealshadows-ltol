#include "US_WeaponProjectileComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "US_BaseWeaponProjectile.h"
#include "US_Character.h"

UUS_WeaponProjectileComponent::UUS_WeaponProjectileComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	ProjectileClass = AUS_BaseWeaponProjectile::StaticClass();
}

void UUS_WeaponProjectileComponent::SetProjectileClass(TSubclassOf<AUS_BaseWeaponProjectile> NewProjectileClass)
{
	ProjectileClass = NewProjectileClass;
}

void UUS_WeaponProjectileComponent::BeginPlay()
{
	Super::BeginPlay();
	
	const auto Character = Cast<AUS_Character>(GetOwner());
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
	if (ProjectileClass)
	{
		const auto Character = Cast<AUS_Character>(GetOwner());
		const auto ProjectileSpawnLocation = GetComponentLocation();
		const auto ProjectileSpawnRotation = GetComponentRotation();

		if (const auto Projectile = GetWorld()->SpawnActor<AUS_BaseWeaponProjectile>(ProjectileClass, ProjectileSpawnLocation, ProjectileSpawnRotation))
		{
			Projectile->SetOwner(Character);
		}
	}
}

//void UUS_WeaponProjectileComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//}

