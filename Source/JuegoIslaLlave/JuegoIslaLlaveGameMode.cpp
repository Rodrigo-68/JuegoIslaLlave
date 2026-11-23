#include "JuegoIslaLlaveGameMode.h"
#include "JuegoIslaLlaveCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Enemy.h"
#include "JuegoFacade.h" // <-- IMPORTANTE: Incluir la Fachada

AJuegoIslaLlaveGameMode::AJuegoIslaLlaveGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

// AQUÍ INICIALIZAMOS LA FACHADA
void AJuegoIslaLlaveGameMode::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World)
	{
		// 1. Instanciamos la Fachada en el mundo
		FActorSpawnParameters Params;
		MiFachada = World->SpawnActor<AJuegoFacade>(AJuegoFacade::StaticClass(), FVector(0, 0, 0), FRotator::ZeroRotator, Params);

		// 2. La Fachada hace todo el trabajo sucio
		if (MiFachada)
		{
			MiFachada->ConfigurarNivel();
		}
	}
}

// Tus funciones de enemigos se quedan intactas
void AJuegoIslaLlaveGameMode::RegisterEnemy(AEnemy* Enemy) { /* ... tu código ... */ }
void AJuegoIslaLlaveGameMode::UnregisterEnemy(AEnemy* Enemy) { /* ... tu código ... */ }
bool AJuegoIslaLlaveGameMode::TryDuplicateEnemy(AEnemy* Source) { return false; /* tu código */ }