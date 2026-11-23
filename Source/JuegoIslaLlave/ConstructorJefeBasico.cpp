#include "ConstructorJefeBasico.h"
#include "Jefe.h"
#include "ArmaJefe.h"
#include "Engine/World.h"

void AConstructorJefeBasico::ConstruirCuerpo(FVector Posicion)
{
	Super::ConstruirCuerpo(Posicion);

	if (Jefe != nullptr)
	{
		Jefe->Nombre = TEXT("Jefe Basico");
		Jefe->Vida = 500;
	}
}

void AConstructorJefeBasico::ConstruirArma()
{
	if (Jefe == nullptr)
	{
		return;
	}

	AArmaJefe* Arma = GetWorld()->SpawnActor<AArmaJefe>();
	Jefe->AdjuntarArma(Arma);
}

void AConstructorJefeBasico::ConstruirEscudo()
{
	// El jefe basico no lleva escudo
}