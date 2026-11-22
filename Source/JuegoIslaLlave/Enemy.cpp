#include "Enemy.h"
#include "PatrolStrategy.h"
#include "IdleStrategy.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "UObject/ConstructorHelpers.h"	
#include "JuegoIslaLlaveGameMode.h"
#include "mina.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->SetBoxExtent(FVector(45.f, 45.f, 45.f));
	CollisionComp->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = CollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(CollisionComp);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// Asigna un mesh por defecto si no se ha asignado uno en el editor
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube_Chamfer.1M_Cube_Chamfer'"));
	if (DefaultMesh.Succeeded())
	{
		MeshComp->SetStaticMesh(DefaultMesh.Object);
	}

	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	DetectionSphere->SetupAttachment(CollisionComp);
	DetectionSphere->SetSphereRadius(DetectionRadius);
	DetectionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DetectionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	DetectionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnDetectionBeginOverlap);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	

	if (AJuegoIslaLlaveGameMode* GM = GetWorld()->GetAuthGameMode<AJuegoIslaLlaveGameMode>())
	{
		GM->RegisterEnemy(this);
	}

	if (MeshComp && MeshComp->GetMaterial(0))
	{
		EnemyMaterial = MeshComp->CreateAndSetMaterialInstanceDynamic(0);
	}
	
	PatrolStrategyObj = NewObject<UPatrolStrategy>(this);
	IdleStrategyObj = NewObject<UIdleStrategy>(this);

	SwitchToPatrol();
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DuplicateCooldownTimer > 0.f)
	{
		DuplicateCooldownTimer -= DeltaTime;
	}

	DetectionSphere->SetSphereRadius(DetectionRadius);
	CheckPlayerProximity();

	// Si est¨¢ patrullando y pasa 10 s sin detectar al jugador, cambia a Idle
	if (!bIsInIdle)
	{
		if (bPlayerInRange)
		{
			TimeWithoutDetection = 0.f;
		}
		else
		{
			TimeWithoutDetection += DeltaTime;
			if (TimeWithoutDetection >= IdleTimeout)
			{
				SwitchToIdle();
			}
		}
	}

	if (UObject* StrategyObj = CurrentStrategy.GetObject())
	{
		if (IEnemyInterface* Strategy = Cast<IEnemyInterface>(StrategyObj))
		{
			Strategy->ExecuteStrategy(this, DeltaTime);
		}
	}
}

void AEnemy::SetStrategy(const TScriptInterface<IEnemyInterface>& NewStrategy)
{
	CurrentStrategy = NewStrategy;
}

void AEnemy::SwitchToPatrol()
{
	bIsInIdle = false;
	TimeWithoutDetection = 0.f;
	SetEnemyColor(FLinearColor::Red);

	if (PatrolStrategyObj)
	{
		PatrolStrategyObj->ResetPatrol();
		SetStrategy(PatrolStrategyObj);
	}
}

void AEnemy::SwitchToIdle()
{
	bIsInIdle = true;
	TimeWithoutDetection = 0.f;

	if (IdleStrategyObj)
	{
		IdleStrategyObj->OnEnterIdle(this);
		SetStrategy(IdleStrategyObj);
	}
	//color
	EnemyMaterial->SetVectorParameterValue(TEXT("Color"), FLinearColor::Green);
	UE_LOG(LogTemp, Warning, TEXT("ENEMIGO: IDLE"));
}

void AEnemy::SetEnemyColor(const FLinearColor& NewColor)
{
	if (EnemyMaterial)
	{
		// Ajusta "Color" si tu material usa otro nombre de par¨¢metro vectorial
		EnemyMaterial->SetVectorParameterValue(TEXT("Color"), NewColor);
	}
}

bool AEnemy::IsPlayerDetected() const
{
	return bPlayerInRange;
}

void AEnemy::UpdateDetectionState(bool bDetected)
{
	bPlayerInRange = bDetected;
	if (bPlayerInRange)
	{
		TimeWithoutDetection = 0.f;
	}
}

void AEnemy::OnDetectionBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (OtherActor && OtherActor == PlayerPawn)
	{
		UpdateDetectionState(true);
	}
}

void AEnemy::CheckPlayerProximity()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!PlayerPawn)
	{
		UpdateDetectionState(false);
		return;
	}

	const float DistanceSq = FVector::DistSquared(GetActorLocation(), PlayerPawn->GetActorLocation());
	const bool bInRadius = DistanceSq <= FMath::Square(DetectionRadius);
	UpdateDetectionState(bInRadius);
}

void AEnemy::TryDuplicateFromIdle()
{
	if (!bIsInIdle || DuplicateCooldownTimer > 0.f)
	{
		return;
	}

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn)
	{
		if (AJuegoIslaLlaveGameMode* GM = GetWorld()->GetAuthGameMode<AJuegoIslaLlaveGameMode>())
		{
			GM->TryDuplicateEnemy(this);
		}
		DuplicateCooldownTimer = DuplicateCooldown;
	}
}




void AEnemy::DropMine()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Amina* NewMine = World->SpawnActor<Amina>(
		Amina::StaticClass(),
		GetActorLocation(),
		FRotator::ZeroRotator,
		Params
	);

	if (NewMine)
	{
		OwnedMines.Add(NewMine);
	}
}

void AEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 1. Destruye ¨²nicamente las minas creadas por este enemigo
	for (Amina* Mine : OwnedMines)
	{
		if (IsValid(Mine))
		{
			Mine->Destroy();
		}
	}
	OwnedMines.Empty();

	// 2. Desregistra al enemigo en el GameMode
	if (UWorld* World = GetWorld())
	{
		if (AJuegoIslaLlaveGameMode* GM = World->GetAuthGameMode<AJuegoIslaLlaveGameMode>())
		{
			GM->UnregisterEnemy(this);
		}
	}

	Super::EndPlay(EndPlayReason);
}
