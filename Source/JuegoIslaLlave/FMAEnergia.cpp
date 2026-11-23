#include "FMAEnergia.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AFMAEnergia::AFMAEnergia()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/state/energia/Ducky_3D_selected_1.Ducky_3D_selected_1'"));
	if (MeshAsset.Succeeded() && AccesorioMesh)
	{
		AccesorioMesh->SetStaticMesh(MeshAsset.Object);
	}
}