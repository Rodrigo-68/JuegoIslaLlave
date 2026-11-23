#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArmaJefe.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class JUEGOISLALLAVE_API AArmaJefe : public AActor
{
	GENERATED_BODY()

public:
	AArmaJefe();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Raiz;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Malla;
};