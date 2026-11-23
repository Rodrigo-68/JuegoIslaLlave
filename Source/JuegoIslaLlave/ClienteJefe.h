#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClienteJefe.generated.h"

UCLASS()
class JUEGOISLALLAVE_API AClienteJefe : public AActor
{
	GENERATED_BODY()

public:
	AClienteJefe();

	// Marcado: jefe completo (arma y escudo). Desmarcado: jefe basico (solo arma)
	UPROPERTY(EditAnywhere)
	bool bJefeCompleto;

protected:
	virtual void BeginPlay() override;
};