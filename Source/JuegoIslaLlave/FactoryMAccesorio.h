#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FMAccesorio.h"
#include "FactoryMAccesorio.generated.h"

UCLASS()
class JUEGOISLALLAVE_API AFactoryMAccesorio : public AActor
{
	GENERATED_BODY()

public:
	AFactoryMAccesorio();

	virtual AFMAccesorio* crearAccesorio(const FVector& Ubicacion, const FRotator& Rotacion = FRotator::ZeroRotator);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};