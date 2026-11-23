// Copyright Epic Games, Inc. All Rights Reserved.

#include "JuegoIslaLlaveGameMode.h"
#include "JuegoIslaLlaveCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Enemy.h"


AJuegoIslaLlaveGameMode::AJuegoIslaLlaveGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}



bool AJuegoIslaLlaveGameMode::TryDuplicateEnemy(AEnemy* Source)
{
	UWorld* World = GetWorld();
	if (!Source || !World || EnemyCount >= MaxEnemies)
	{
		return false;
	}

	const FVector Offset = FRotator(0.f, FMath::FRandRange(0.f, 360.f), 0.f).Vector() * 200.f;

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AEnemy* NewEnemy = World->SpawnActor<AEnemy>(
		Source->GetClass(),
		Source->GetActorLocation() + Offset,
		Source->GetActorRotation(),
		Params);

	return NewEnemy != nullptr;
}

void AJuegoIslaLlaveGameMode::RegisterEnemy(AEnemy* Enemy)
{
	if (!Enemy)
	{
		return;
	}

	// Conecta al nuevo con los que ya existen, en ambos sentidos
	for (AEnemy* Other : Enemies)
	{
		if (IsValid(Other))
		{
			Other->Attach(Enemy);
			Enemy->Attach(Other);
		}
	}
	Enemies.Add(Enemy);

	++EnemyCount;
	UE_LOG(LogTemp, Warning, TEXT("Enemigos: %d"), EnemyCount);
}

void AJuegoIslaLlaveGameMode::UnregisterEnemy(AEnemy* Enemy)
{
	Enemies.Remove(Enemy);
	for (AEnemy* Other : Enemies)
	{
		if (IsValid(Other))
		{
			Other->Detach(Enemy);
		}
	}

	EnemyCount = FMath::Max(0, EnemyCount - 1);
	UE_LOG(LogTemp, Warning, TEXT("Enemigos: %d"), EnemyCount);
}