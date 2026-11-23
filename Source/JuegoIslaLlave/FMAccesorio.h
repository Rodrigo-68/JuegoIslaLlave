#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FMAccesorio.generated.h"

UCLASS()
class JUEGOISLALLAVE_API AFMAccesorio : public AActor
{
	GENERATED_BODY()

public:
	AFMAccesorio();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	class UStaticMeshComponent* AccesorioMesh;

	virtual void SoltarEnUbicacion(const FVector& Ubicacion, const FRotator& Rotacion);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};