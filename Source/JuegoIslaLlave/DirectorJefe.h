#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DirectorJefe.generated.h"

class AConstructorJefe;
class AJefe;

UCLASS()
class JUEGOISLALLAVE_API ADirectorJefe : public AActor
{
	GENERATED_BODY()

public:
	ADirectorJefe();

	// Recibe el constructor que se va a usar
	void SetConstructor(AConstructorJefe* NuevoConstructor);

	// Recetas del director
	void ConstruirJefeBasico(FVector Posicion);
	void ConstruirJefeCompleto(FVector Posicion);

	AJefe* ObtenerJefe();

private:
	UPROPERTY()
	AConstructorJefe* Constructor;
};