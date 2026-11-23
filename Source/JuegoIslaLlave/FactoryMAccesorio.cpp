#include "FactoryMAccesorio.h"
#include "Engine/World.h"

AFactoryMAccesorio::AFactoryMAccesorio()
{
	PrimaryActorTick.bCanEverTick = false;
}

AFMAccesorio* AFactoryMAccesorio::crearAccesorio(const FVector& Ubicacion, const FRotator& Rotacion)
{
	return nullptr;
}

void AFactoryMAccesorio::BeginPlay()
{
	Super::BeginPlay();
}

void AFactoryMAccesorio::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}