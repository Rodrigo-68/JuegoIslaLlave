#pragma once

#include "CoreMinimal.h"
#include "FactoryMAccesorio.h"
#include "FactoryMALlave.generated.h"

UCLASS()
class JUEGOISLALLAVE_API AFactoryMALlave : public AFactoryMAccesorio
{
	GENERATED_BODY()

public:
	virtual AFMAccesorio* crearAccesorio(const FVector& Ubicacion, const FRotator& Rotacion = FRotator::ZeroRotator) override;
};