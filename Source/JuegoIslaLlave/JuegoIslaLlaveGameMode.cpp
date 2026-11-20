// Copyright Epic Games, Inc. All Rights Reserved.

#include "JuegoIslaLlaveGameMode.h"
#include "JuegoIslaLlaveCharacter.h"
#include "UObject/ConstructorHelpers.h"

AJuegoIslaLlaveGameMode::AJuegoIslaLlaveGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
