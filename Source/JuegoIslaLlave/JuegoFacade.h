#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JuegoFacade.generated.h"

class ADirectorJefe;
class AConstructorJefeBasico;
class AConstructorJefeAvanzado;

class AFactoryMALlave;

UCLASS()
class JUEGOISLALLAVE_API AJuegoFacade : public AActor
{
	GENERATED_BODY()

public:
	AJuegoFacade();

	// Función principal que llamará el GameMode
	void ConfigurarNivel();

private:
	void ConfigurarJefe(int32 NivelActual);
	void ConfigurarObjetosDelJuego();
	void ConfigurarPortalYEstado();
};