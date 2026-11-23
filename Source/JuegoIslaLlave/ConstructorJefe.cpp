#include "ConstructorJefe.h"
#include "Jefe.h"
#include "Engine/World.h"

AConstructorJefe::AConstructorJefe()
{
	PrimaryActorTick.bCanEverTick = false;
	Jefe = nullptr;
}

void AConstructorJefe::ConstruirCuerpo(FVector Posicion)
{
	// Crea el jefe base en el mundo
	Jefe = GetWorld()->SpawnActor<AJefe>(Posicion, FRotator::ZeroRotator);
}

void AConstructorJefe::ConstruirArma()
{
	// Se redefine en los constructores concretos
}

void AConstructorJefe::ConstruirEscudo()
{
	// Se redefine en los constructores concretos
}

AJefe* AConstructorJefe::ObtenerJefe()
{
	return Jefe;
}