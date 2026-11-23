// Fill out your copyright notice in the Description page of Project Settings.

#include "STeletransportar.h"
#include "SPortal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

void USTeletransportar::Inicializar(ASPortal* InPortal)
{
	Portal = InPortal;
}

void USTeletransportar::contactoEnergia()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Yellow, TEXT("Portal: Ya esta listo para teletransportar"));
	}
}

void USTeletransportar::contactoJugador()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, TEXT("Portal: Teletransportando jugador"));
	}

	if (Portal)
	{
		if (UWorld* World = Portal->GetWorld())
		{
			if (ACharacter* Jugador = UGameplayStatics::GetPlayerCharacter(World, 0))
			{
				FVector Destino = Portal->CoordenadaFijaTeletransporte;
				Jugador->TeleportTo(Destino, Jugador->GetActorRotation(), false, true);
			}
		}

		Portal->SetState(Portal->GetSSinEnergia());
	}
}

void USTeletransportar::contactoLlave()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Yellow, TEXT("Portal: Llave ignorada en estado teletransportar"));
	}
}