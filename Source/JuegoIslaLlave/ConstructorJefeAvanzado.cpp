#include "ConstructorJefeAvanzado.h"
#include "Jefe.h"
#include "ArmaJefe.h"
#include "EscudoJefe.h"
#include "Engine/World.h"

void AConstructorJefeAvanzado::ConstruirCuerpo(FVector Posicion)
{
	Super::ConstruirCuerpo(Posicion);

	if (Jefe != nullptr)
	{
		Jefe->Nombre = TEXT("Jefe Avanzado");
		Jefe->Vida = 1000;
	}
}

void AConstructorJefeAvanzado::ConstruirArma()
{
	if (Jefe == nullptr)
	{
		return;
	}

	AArmaJefe* Arma = GetWorld()->SpawnActor<AArmaJefe>();
	Jefe->AdjuntarArma(Arma);
}

void AConstructorJefeAvanzado::ConstruirEscudo()
{
	if (Jefe == nullptr)
	{
		return;
	}

	AEscudoJefe* Escudo = GetWorld()->SpawnActor<AEscudoJefe>();
	Jefe->AdjuntarEscudo(Escudo);
}