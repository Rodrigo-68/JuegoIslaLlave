#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StatePortal.generated.h"

UINTERFACE(MinimalAPI)
class UStatePortal : public UInterface
{
	GENERATED_BODY()
};

class JUEGOISLALLAVE_API IStatePortal
{
	GENERATED_BODY()

public:
	virtual void contactoEnergia() = 0;
	virtual void contactoJugador() = 0;
	virtual void contactoLlave() = 0;
};