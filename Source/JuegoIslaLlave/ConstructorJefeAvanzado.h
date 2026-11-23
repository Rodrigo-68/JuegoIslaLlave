#pragma once

#include "CoreMinimal.h"
#include "ConstructorJefe.h"
#include "ConstructorJefeAvanzado.generated.h"

UCLASS()
class JUEGOISLALLAVE_API AConstructorJefeAvanzado : public AConstructorJefe
{
	GENERATED_BODY()

public:
	virtual void ConstruirCuerpo(FVector Posicion) override;
	virtual void ConstruirArma() override;
	virtual void ConstruirEscudo() override;
};