// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StatePortal.h"
#include "SSinEnergia.h"
#include "SRecargado.h"
#include "SGenerarLlave.h"
#include "SCerrado.h"
#include "SAbierto.h"
#include "STeletransportar.h"
#include "SPortal.generated.h"

class AFactoryMALlave;

UCLASS()
class JUEGOISLALLAVE_API ASPortal : public AActor
{
	GENERATED_BODY()

public:
	ASPortal();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	class UStaticMeshComponent* PortalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Llave")
	float DistanciaSpawnLlave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal|Config")
	FVector UbicacionFijaPortal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal|Config")
	FVector CoordenadaFijaTeletransporte;

	UPROPERTY()
	USSinEnergia* SSinEnergiaObj;

	UPROPERTY()
	USRecargado* SRecargadoObj;

	UPROPERTY()
	USGenerarLlave* SGenerarLlaveObj;

	UPROPERTY()
	USCerrado* SCerradoObj;

	UPROPERTY()
	USAbierto* SAbiertoObj;

	UPROPERTY()
	USTeletransportar* STeletransportarObj;

	UPROPERTY()
	TScriptInterface<IStatePortal> CurrentState;

	UPROPERTY()
	AFactoryMALlave* FabricaLlave;

	void ConfigurarPortal(const FVector& NuevaUbicacionPortal, const FVector& NuevaCoordenadaTeletransporte);
	void SetState(TScriptInterface<IStatePortal> NewState);
	void GenerarLlaveAlrededor();

	FORCEINLINE TScriptInterface<IStatePortal> GetSSinEnergia() const { return SSinEnergiaObj; }
	FORCEINLINE TScriptInterface<IStatePortal> GetSRecargado() const { return SRecargadoObj; }
	FORCEINLINE TScriptInterface<IStatePortal> GetSGenerarLlave() const { return SGenerarLlaveObj; }
	FORCEINLINE TScriptInterface<IStatePortal> GetSCerrado() const { return SCerradoObj; }
	FORCEINLINE TScriptInterface<IStatePortal> GetSAbierto() const { return SAbiertoObj; }
	FORCEINLINE TScriptInterface<IStatePortal> GetSTeletransportar() const { return STeletransportarObj; }

	UFUNCTION()
	void OnPortalBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};