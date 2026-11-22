// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JuegoIslaLlaveGameMode.generated.h"


UCLASS(minimalapi)
class AJuegoIslaLlaveGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AJuegoIslaLlaveGameMode();

public:
	void RegisterEnemy(class AEnemy* Enemy);
	void UnregisterEnemy(class AEnemy* Enemy);
	bool TryDuplicateEnemy(class AEnemy* Source);

private:
	int32 EnemyCount = 0;

	UPROPERTY(EditAnywhere, Category = "Enemies")
	int32 MaxEnemies = 10;
};



