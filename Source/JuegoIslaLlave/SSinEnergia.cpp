#include "SSinEnergia.h"
#include "SPortal.h"
#include "Engine/Engine.h"

void USSinEnergia::Inicializar(ASPortal* InPortal)
{
	Portal = InPortal;
}

void USSinEnergia::contactoEnergia()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, TEXT("Portal: Energia recibida -> Recargado"));
	}
	if (Portal)
	{
		Portal->SetState(Portal->GetSRecargado());
	}
}

void USSinEnergia::contactoJugador()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, TEXT("Portal: Sin energia"));
	}
}

void USSinEnergia::contactoLlave()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Yellow, TEXT("Portal: Sin energia para llave"));
	}
}