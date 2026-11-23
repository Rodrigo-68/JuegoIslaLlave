#include "FMAccesorio.h"
#include "Components/StaticMeshComponent.h"

AFMAccesorio::AFMAccesorio()
{
	PrimaryActorTick.bCanEverTick = false;

	AccesorioMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AccesorioMesh"));
	RootComponent = AccesorioMesh;
	AccesorioMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	AccesorioMesh->SetGenerateOverlapEvents(true);
}

void AFMAccesorio::BeginPlay()
{
	Super::BeginPlay();
}

void AFMAccesorio::SoltarEnUbicacion(const FVector& Ubicacion, const FRotator& Rotacion)
{
	SetActorLocationAndRotation(Ubicacion, Rotacion);
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

void AFMAccesorio::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}