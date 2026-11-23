// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JuegoIslaLlaveGameMode.generated.h"

class AJuegoFacade;

UCLASS(minimalapi)
class AJuegoIslaLlaveGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AJuegoIslaLlaveGameMode();

	// Métodos de enemigos que ya tenías
	void RegisterEnemy(class AEnemy* Enemy);
	void UnregisterEnemy(class AEnemy* Enemy);
	bool TryDuplicateEnemy(class AEnemy* Source);

protected:
	virtual void BeginPlay() override;

private:
	int32 EnemyCount = 0;

	UPROPERTY(EditAnywhere, Category = "Enemies")
	int32 MaxEnemies = 10;

	// Puntero a tu Fachada
	UPROPERTY()
	AJuegoFacade* MiFachada;
};