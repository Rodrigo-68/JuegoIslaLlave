#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EscudoJefe.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class JUEGOISLALLAVE_API AEscudoJefe : public AActor
{
	GENERATED_BODY()

public:
	AEscudoJefe();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Raiz;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Malla;
};