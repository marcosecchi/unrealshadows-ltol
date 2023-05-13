#include "US_WeaponProjectileComponent.h"

UUS_WeaponProjectileComponent::UUS_WeaponProjectileComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UUS_WeaponProjectileComponent::SetProjectileClass(TSubclassOf<AUS_BaseWeaponProjectile> NewProjectileClass)
{
	ProjectileClass = NewProjectileClass;
}


// Called when the game starts
void UUS_WeaponProjectileComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UUS_WeaponProjectileComponent::Throw()
{
	
}


void UUS_WeaponProjectileComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

