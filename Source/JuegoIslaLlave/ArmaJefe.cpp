#include "ArmaJefe.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"

AArmaJefe::AArmaJefe()
{
	PrimaryActorTick.bCanEverTick = false;

	Raiz = CreateDefaultSubobject<USceneComponent>(TEXT("Raiz"));
	RootComponent = Raiz;

	Malla = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla"));
	Malla->SetupAttachment(Raiz);
	Malla->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// El arma es una espada: un cubo alargado
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cubo(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (Cubo.Succeeded())
	{
		Malla->SetStaticMesh(Cubo.Object);
	}

	Malla->SetRelativeScale3D(FVector(0.1f, 0.1f, 1.8f));
}