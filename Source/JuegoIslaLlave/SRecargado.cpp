#include "SRecargado.h"
#include "SPortal.h"
#include "Engine/Engine.h"

void USRecargado::Inicializar(ASPortal* InPortal)
{
	Portal = InPortal;
}

void USRecargado::contactoEnergia()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Yellow, TEXT("Portal: Ya esta recargado"));
	}
}

void USRecargado::contactoJugador()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Cyan, TEXT("Portal: Jugador -> Generar Llave"));
	}
	if (Portal)
	{
		Portal->SetState(Portal->GetSGenerarLlave());
	}
	if (Portal)
	{
		Portal->SetState(Portal->GetSCerrado());
	}
}

void USRecargado::contactoLlave()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Yellow, TEXT("Portal: Aun no genera llave"));
	}
}