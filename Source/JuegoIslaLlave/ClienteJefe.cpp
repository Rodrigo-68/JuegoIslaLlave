#include "ClienteJefe.h"
#include "DirectorJefe.h"
#include "ConstructorJefe.h"
#include "ConstructorJefeBasico.h"
#include "ConstructorJefeAvanzado.h"
#include "Jefe.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"

AClienteJefe::AClienteJefe()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Raiz"));
	bJefeCompleto = true;
}

void AClienteJefe::BeginPlay()
{
	Super::BeginPlay();

	UWorld* Mundo = GetWorld();
	if (Mundo == nullptr)
	{
		return;
	}

	// El jefe aparece donde esta este actor
	FVector Posicion = GetActorLocation();

	// 1. Se crea el Director
	ADirectorJefe* Director = Mundo->SpawnActor<ADirectorJefe>();

	// 2. Se crea el Constructor y se construye con la receta del Director
	if (bJefeCompleto)
	{
		AConstructorJefeAvanzado* Constructor = Mundo->SpawnActor<AConstructorJefeAvanzado>();
		Director->SetConstructor(Constructor);
		Director->ConstruirJefeCompleto(Posicion);
	}
	else
	{
		AConstructorJefeBasico* Constructor = Mundo->SpawnActor<AConstructorJefeBasico>();
		Director->SetConstructor(Constructor);
		Director->ConstruirJefeBasico(Posicion);
	}

	// 3. Se obtiene el jefe terminado
	AJefe* Jefe = Director->ObtenerJefe();
	if (Jefe != nullptr)
	{
		Jefe->MostrarDatos();
	}
}