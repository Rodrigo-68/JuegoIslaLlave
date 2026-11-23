#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Jefe.generated.h"

class AArmaJefe;
class AEscudoJefe;

UCLASS()
class JUEGOISLALLAVE_API AJefe : public AActor
{
	GENERATED_BODY()

public:
	AJefe();

	UPROPERTY(VisibleAnywhere) USceneComponent* Raiz;

	UPROPERTY(VisibleAnywhere) USkeletalMeshComponent* Malla;

	UPROPERTY(EditAnywhere) FString Nombre;

	UPROPERTY(EditAnywhere) int32 Vida;

	// Metodos para acoplar los componentes al jefe
	void AdjuntarArma(AArmaJefe* Arma);
	void AdjuntarEscudo(AEscudoJefe* Escudo);

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Ataque") float RangoDeteccion = 1200.f;
	UPROPERTY(EditAnywhere, Category = "Ataque") float RangoAtaque = 350.f;
	UPROPERTY(EditAnywhere, Category = "Ataque") float Danio = 20.f;
	UPROPERTY(EditAnywhere, Category = "Ataque") float Cooldown = 2.f;

	// Muestra los datos del jefe en pantalla
	void MostrarDatos();

private:
	bool TieneArma;
	bool TieneEscudo;
	float TiempoDesdeAtaque = 0.f;
	void Atacar(AActor* Objetivo);
};