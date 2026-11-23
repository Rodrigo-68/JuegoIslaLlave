#include "SGenerarLlave.h"
#include "SPortal.h"
#include "Engine/Engine.h"

void USGenerarLlave::Inicializar(ASPortal* InPortal)
{
	Portal = InPortal;
}

void USGenerarLlave::contactoEnergia()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Yellow, TEXT("Portal: Generando llave"));
	}
}

void USGenerarLlave::contactoJugador()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Yellow, TEXT("Portal: Llave lista alrededor"));
	}
}

void USGenerarLlave::contactoLlave()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, TEXT("Portal: Llave -> Cerrado"));
	}
	if (Portal)
	{
		Portal->SetState(Portal->GetSCerrado());
	}
}