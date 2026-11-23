#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mina.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class JUEGOISLALLAVE_API Amina : public AActor
{
	GENERATED_BODY()

public:
	Amina();

protected:
	UFUNCTION()
	void OnMineBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* TriggerSphere;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;
};