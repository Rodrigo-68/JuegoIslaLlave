#include "FactoryMALlave.h"
#include "FMALlave.h"
#include "Engine/World.h"

AFMAccesorio* AFactoryMALlave::crearAccesorio(const FVector& Ubicacion, const FRotator& Rotacion)
{
	UWorld* World = GetWorld();
	if (World)
	{
		return World->SpawnActor<AFMALlave>(AFMALlave::StaticClass(), Ubicacion, Rotacion);
	}
	return nullptr;
}