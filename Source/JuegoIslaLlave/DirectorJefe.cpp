#include "DirectorJefe.h"
#include "ConstructorJefe.h"
#include "Jefe.h"

ADirectorJefe::ADirectorJefe()
{
	PrimaryActorTick.bCanEverTick = false;
	Constructor = nullptr;
}

void ADirectorJefe::SetConstructor(AConstructorJefe* NuevoConstructor)
{
	Constructor = NuevoConstructor;
}

// Receta 1: cuerpo y arma
void ADirectorJefe::ConstruirJefeBasico(FVector Posicion)
{
	if (Constructor == nullptr)
	{
		return;
	}

	Constructor->ConstruirCuerpo(Posicion);
	Constructor->ConstruirArma();
}

// Receta 2: cuerpo, arma y escudo
void ADirectorJefe::ConstruirJefeCompleto(FVector Posicion)
{
	if (Constructor == nullptr)
	{
		return;
	}

	Constructor->ConstruirCuerpo(Posicion);
	Constructor->ConstruirArma();
	Constructor->ConstruirEscudo();
}

AJefe* ADirectorJefe::ObtenerJefe()
{
	if (Constructor == nullptr)
	{
		return nullptr;
	}

	return Constructor->ObtenerJefe();
}