#include "FactoryMAEnergia.h"
#include "FMAEnergia.h"
#include "Engine/World.h"

AFMAccesorio* AFactoryMAEnergia::crearAccesorio(const FVector& Ubicacion, const FRotator& Rotacion)
{
	UWorld* World = GetWorld();
	if (World)
	{
		return World->SpawnActor<AFMAEnergia>(AFMAEnergia::StaticClass(), Ubicacion, Rotacion);
	}
	return nullptr;
}