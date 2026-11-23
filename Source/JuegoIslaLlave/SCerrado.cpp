#include "SCerrado.h"
#include "SPortal.h"
#include "Engine/Engine.h"

void USCerrado::Inicializar(ASPortal* InPortal)
{
	Portal = InPortal;
}

void USCerrado::contactoEnergia()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Yellow, TEXT("Portal: Cerrado"));
	}
}

void USCerrado::contactoJugador()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Yellow, TEXT("Portal: Cerrado, necesita llave"));
	}
}

void USCerrado::contactoLlave()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, TEXT("Portal: Llave -> Abierto"));
	}
	if (Portal)
	{
		Portal->SetState(Portal->GetSAbierto());
	}
}