#pragma once

#include "CoreMinimal.h"
#include "ConstructorJefe.h"
#include "ConstructorJefeBasico.generated.h"

UCLASS()
class JUEGOISLALLAVE_API AConstructorJefeBasico : public AConstructorJefe
{
	GENERATED_BODY()

public:
	virtual void ConstruirCuerpo(FVector Posicion) override;
	virtual void ConstruirArma() override;
	virtual void ConstruirEscudo() override;
};