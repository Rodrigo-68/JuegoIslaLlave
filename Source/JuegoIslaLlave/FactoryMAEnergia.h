#pragma once

#include "CoreMinimal.h"
#include "FactoryMAccesorio.h"
#include "FactoryMAEnergia.generated.h"

UCLASS()
class JUEGOISLALLAVE_API AFactoryMAEnergia : public AFactoryMAccesorio
{
	GENERATED_BODY()

public:
	virtual AFMAccesorio* crearAccesorio(const FVector& Ubicacion, const FRotator& Rotacion = FRotator::ZeroRotator) override;
};