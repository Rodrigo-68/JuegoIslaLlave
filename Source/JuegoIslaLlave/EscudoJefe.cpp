#include "EscudoJefe.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"

AEscudoJefe::AEscudoJefe()
{
	PrimaryActorTick.bCanEverTick = false;

	Raiz = CreateDefaultSubobject<USceneComponent>(TEXT("Raiz"));
	RootComponent = Raiz;

	Malla = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla"));
	Malla->SetupAttachment(Raiz);
	Malla->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// El escudo es un cilindro aplanado
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cilindro(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (Cilindro.Succeeded())
	{
		Malla->SetStaticMesh(Cilindro.Object);
	}

	Malla->SetRelativeScale3D(FVector(1.2f, 1.2f, 0.1f));
	Malla->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
}