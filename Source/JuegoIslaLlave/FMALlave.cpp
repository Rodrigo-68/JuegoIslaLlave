#include "FMALlave.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AFMALlave::AFMALlave()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/state/portal/Portal_BrickSmall_low.Portal_BrickSmall_low'"));
	if (MeshAsset.Succeeded() && AccesorioMesh)
	{
		AccesorioMesh->SetStaticMesh(MeshAsset.Object);
	}

}