#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StatePortal.h"
#include "SAbierto.generated.h"

class ASPortal;

UCLASS()
class JUEGOISLALLAVE_API USAbierto : public UObject, public IStatePortal
{
	GENERATED_BODY()

private:
	UPROPERTY()
	ASPortal* Portal;

public:
	void Inicializar(ASPortal* InPortal);

	virtual void contactoEnergia() override;
	virtual void contactoJugador() override;
	virtual void contactoLlave() override;
};