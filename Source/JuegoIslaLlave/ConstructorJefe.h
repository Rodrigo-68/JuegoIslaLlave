#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConstructorJefe.generated.h"

class AJefe;

UCLASS(Abstract)
class JUEGOISLALLAVE_API AConstructorJefe : public AActor
{
	GENERATED_BODY()

public:
	AConstructorJefe();

	// Pasos de construccion: cada constructor concreto los redefine
	virtual void ConstruirCuerpo(FVector Posicion);
	virtual void ConstruirArma();
	virtual void ConstruirEscudo();

	AJefe* ObtenerJefe();

protected:
	UPROPERTY()
	AJefe* Jefe;
};