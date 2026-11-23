#include "Jefe.h"
#include "ArmaJefe.h"
#include "EscudoJefe.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "UObject/ConstructorHelpers.h"

AJefe::AJefe()
{
	PrimaryActorTick.bCanEverTick = true;

	Nombre = TEXT("Jefe");
	Vida = 100;
	TieneArma = false;
	TieneEscudo = false;

	Raiz = CreateDefaultSubobject<USceneComponent>(TEXT("Raiz"));
	RootComponent = Raiz;

	Malla = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Malla"));
	Malla->SetupAttachment(Raiz);
	Malla->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	Malla->SetRelativeScale3D(FVector(100.f, 100.f, 100.f));

	// IMPORTANTE: cambia esta ruta por la de tu malla (ver Paso 5)
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> MallaJefe(
		TEXT("/Game/mallas/Enemigos/jefe_Enemigo/BOSS_model_final.BOSS_model_final"));
	if (MallaJefe.Succeeded())
	{
		Malla->SetSkeletalMesh(MallaJefe.Object);
	}
}

void AJefe::AdjuntarArma(AArmaJefe* Arma)
{
	if (Arma == nullptr)
	{
		return;
	}

	Arma->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	Arma->SetActorRelativeLocation(FVector(-150.f, 70.f, 120.f));
	TieneArma = true;
}

void AJefe::AdjuntarEscudo(AEscudoJefe* Escudo)
{
	if (Escudo == nullptr)
	{
		return;
	}

	Escudo->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	Escudo->SetActorRelativeLocation(FVector(40.f, -90.f, 100.f));
	TieneEscudo = true;
}

void AJefe::MostrarDatos()
{
	FString Texto = Nombre + TEXT(" | Vida: ") + FString::FromInt(Vida);

	if (TieneArma)
	{
		Texto += TEXT(" | Con arma");
	}
	if (TieneEscudo)
	{
		Texto += TEXT(" | Con escudo");
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Yellow, Texto);
	}
}

void AJefe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AActor* Jugador = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!Jugador)
	{
		return;
	}

	const float Distancia = FVector::Dist(GetActorLocation(), Jugador->GetActorLocation());
	if (Distancia > RangoDeteccion)
	{
		return;
	}

	// Mirar al jugador (solo giro horizontal)
	FRotator Mirar = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Jugador->GetActorLocation());
	Mirar.Pitch = 0.f;
	Mirar.Roll = 0.f;
	SetActorRotation(Mirar);

	TiempoDesdeAtaque += DeltaTime;
	if (Distancia <= RangoAtaque && TiempoDesdeAtaque >= Cooldown)
	{
		Atacar(Jugador);
		TiempoDesdeAtaque = 0.f;
	}
}

void AJefe::Atacar(AActor* Objetivo)
{
	UGameplayStatics::ApplyDamage(Objetivo, Danio, nullptr, this, nullptr);

	if (ACharacter* Personaje = Cast<ACharacter>(Objetivo))
	{
		FVector Empuje = (Objetivo->GetActorLocation() - GetActorLocation()).GetSafeNormal() * 800.f;
		Empuje.Z = 300.f;
		Personaje->LaunchCharacter(Empuje, true, true);
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("El jefe te golpeo!"));
	}
}