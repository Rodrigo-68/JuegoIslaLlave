// Fill out your copyright notice in the Description page of Project Settings.

#include "SPortal.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "FMAEnergia.h"
#include "FMALlave.h"
#include "FactoryMALlave.h"
#include "JuegoIslaLlaveCharacter.h"

ASPortal::ASPortal()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/state/portal/Portal_BrickLarge_low.Portal_BrickLarge_low'"));
	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	if (MeshAsset.Succeeded())
	{
		PortalMesh->SetStaticMesh(MeshAsset.Object);
	}
	RootComponent = PortalMesh;

	PortalMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	PortalMesh->SetGenerateOverlapEvents(true);
	PortalMesh->OnComponentBeginOverlap.AddDynamic(this, &ASPortal::OnPortalBeginOverlap);

	DistanciaSpawnLlave = 500.f;
	UbicacionFijaPortal = FVector::ZeroVector;
	CoordenadaFijaTeletransporte = FVector::ZeroVector;
}

void ASPortal::ConfigurarPortal(const FVector& NuevaUbicacionPortal, const FVector& NuevaCoordenadaTeletransporte)
{
	UbicacionFijaPortal = NuevaUbicacionPortal;
	CoordenadaFijaTeletransporte = NuevaCoordenadaTeletransporte;
	SetActorLocation(UbicacionFijaPortal);
}

void ASPortal::BeginPlay()
{
	Super::BeginPlay();

	if (!UbicacionFijaPortal.IsNearlyZero())
	{
		SetActorLocation(UbicacionFijaPortal);
	}

	if (UWorld* World = GetWorld())
	{
		FabricaLlave = World->SpawnActor<AFactoryMALlave>(AFactoryMALlave::StaticClass(), GetActorLocation(), FRotator::ZeroRotator);
	}

	SSinEnergiaObj = NewObject<USSinEnergia>(this);
	SSinEnergiaObj->Inicializar(this);

	SRecargadoObj = NewObject<USRecargado>(this);
	SRecargadoObj->Inicializar(this);

	SGenerarLlaveObj = NewObject<USGenerarLlave>(this);
	SGenerarLlaveObj->Inicializar(this);

	SCerradoObj = NewObject<USCerrado>(this);
	SCerradoObj->Inicializar(this);

	SAbiertoObj = NewObject<USAbierto>(this);
	SAbiertoObj->Inicializar(this);

	STeletransportarObj = NewObject<USTeletransportar>(this);
	STeletransportarObj->Inicializar(this);

	CurrentState = SSinEnergiaObj;
}

void ASPortal::SetState(TScriptInterface<IStatePortal> NewState)
{
	CurrentState = NewState;

	if (CurrentState.GetObject() == SGenerarLlaveObj)
	{
		GenerarLlaveAlrededor();
	}
}

void ASPortal::GenerarLlaveAlrededor()
{
	if (FabricaLlave)
	{
		float Angulo = FMath::RandRange(0.f, 2.f * PI);
		FVector Desplazamiento(FMath::Cos(Angulo) * DistanciaSpawnLlave, FMath::Sin(Angulo) * DistanciaSpawnLlave, 0.f);
		FVector SpawnLocation = GetActorLocation() + Desplazamiento;

		FabricaLlave->crearAccesorio(SpawnLocation, FRotator::ZeroRotator);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, TEXT("Llave generada alrededor del portal"));
		}
	}
}

void ASPortal::OnPortalBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this || !CurrentState)
	{
		return;
	}

	if (OtherActor->IsA(AFMAEnergia::StaticClass()))
	{
		CurrentState->contactoEnergia();
		OtherActor->Destroy();
	}
	else if (OtherActor->IsA(AFMALlave::StaticClass()))
	{
		CurrentState->contactoLlave();
		OtherActor->Destroy();
	}
	else if (OtherActor->IsA(AJuegoIslaLlaveCharacter::StaticClass()))
	{
		CurrentState->contactoJugador();
	}
}

void ASPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}