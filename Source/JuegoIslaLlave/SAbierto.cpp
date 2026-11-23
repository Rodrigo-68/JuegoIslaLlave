#include "SAbierto.h"
#include "SPortal.h"
#include "Engine/Engine.h"

void USAbierto::Inicializar(ASPortal* InPortal)
{
	Portal = InPortal;
}

void USAbierto::contactoEnergia()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Yellow, TEXT("Portal: Ya esta abierto"));
	}
}

void USAbierto::contactoJugador()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Magenta, TEXT("Portal: Jugador -> Teletransportar"));
	}
	if (Portal)
	{
		Portal->SetState(Portal->GetSTeletransportar());
	}
}

void USAbierto::contactoLlave()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Yellow, TEXT("Portal: Ya esta abierto"));
	}
}