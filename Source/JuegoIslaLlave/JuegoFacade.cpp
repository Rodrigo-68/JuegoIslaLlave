#include "JuegoFacade.h"
#include "Kismet/GameplayStatics.h"
#include "DirectorJefe.h"
#include "ConstructorJefeBasico.h"
#include "ConstructorJefeAvanzado.h"
#include "FactoryMALlave.h" 

AJuegoFacade::AJuegoFacade()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AJuegoFacade::ConfigurarNivel()
{
	FString NombreNivel = UGameplayStatics::GetCurrentLevelName(GetWorld());
	UE_LOG(LogTemp, Warning, TEXT("Facade: Iniciando configuracion del nivel %s"), *NombreNivel);

	// 1. Configuramos al Jefe (Tu patrón Builder)
	if (NombreNivel.Contains("Nivel3"))
	{
		ConfigurarJefe(2); // Jefe Avanzado
	}
	else
	{
		ConfigurarJefe(1); // Jefe Básico
	}

	// 2. Configuramos los objetos (Factory Method)
	ConfigurarObjetosDelJuego();

	// 3. Configuramos el portal (State)
	ConfigurarPortalYEstado();
}

// ==========================================
// TU PATRÓN BUILDER
// ==========================================
void AJuegoFacade::ConfigurarJefe(int32 NivelActual)
{
	FActorSpawnParameters Params;
	ADirectorJefe* Director = GetWorld()->SpawnActor<ADirectorJefe>(ADirectorJefe::StaticClass(), Params);

	// Posición donde aparecerá el Jefe
	FVector PosicionJefe = FVector(0.0f, 0.0f, 100.0f);

	if (NivelActual == 1)
	{
		AConstructorJefeBasico* BuilderBasico = GetWorld()->SpawnActor<AConstructorJefeBasico>(AConstructorJefeBasico::StaticClass(), Params);
		Director->SetConstructor(BuilderBasico);
		Director->ConstruirJefeBasico(PosicionJefe);
	}
	else
	{
		AConstructorJefeAvanzado* BuilderAvanzado = GetWorld()->SpawnActor<AConstructorJefeAvanzado>(AConstructorJefeAvanzado::StaticClass(), Params);
		Director->SetConstructor(BuilderAvanzado);
		Director->ConstruirJefeCompleto(PosicionJefe);
	}
}

// ==========================================
// FACTORY METHOD DE TU COMPAÑERO
// ==========================================
void AJuegoFacade::ConfigurarObjetosDelJuego()
{
	FActorSpawnParameters Params;

	// ¡CORREGIDO! Usamos AFactoryMALlave (con L mayúscula)
	if (AFactoryMALlave* FabricaLlave = GetWorld()->SpawnActor<AFactoryMALlave>(AFactoryMALlave::StaticClass(), Params))
	{
		// Aquí puedes llamar a sus métodos. 
		// Según su .h, el método se llama crearAccesorio y pide FVector y FRotator
		// FabricaLlave->crearAccesorio(FVector(0,0,0), FRotator(0,0,0)); 
	}

	UE_LOG(LogTemp, Warning, TEXT("Facade: Objetos instanciados (Factory)"));
}

// ==========================================
// STATE DE TU COMPAÑERO (PORTAL)
// ==========================================
void AJuegoFacade::ConfigurarPortalYEstado()
{
	// Lo dejamos solo con el mensaje de log por ahora para que compile.
	UE_LOG(LogTemp, Warning, TEXT("Facade: Portal configurado (State)"));
}