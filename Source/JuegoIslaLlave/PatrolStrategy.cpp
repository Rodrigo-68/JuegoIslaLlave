#include "PatrolStrategy.h"
#include "Enemy.h"

UPatrolStrategy::UPatrolStrategy()
	: Direction(FVector::ZeroVector)
	, PatrolSpeed(200.f)
	, TimeToChange(0.f)
	, TimeToMine(2.f)
	, MineInterval(2.f)
{
}

void UPatrolStrategy::ResetPatrol()
{
	TimeToChange = 0.f;
	TimeToMine = MineInterval;
	PickNewDirection();
}

void UPatrolStrategy::PickNewDirection()
{
	// Direcci車n aleatoria en el plano horizontal (XY)
	const float Angle = FMath::FRandRange(0.f, 360.f);
	Direction = FRotator(0.f, Angle, 0.f).Vector();
	Direction.Z = 0.f;
	Direction.Normalize();

	// Mantiene esa direcci車n entre 1 y 3 segundos
	TimeToChange = FMath::FRandRange(1.f, 3.f);
}

void UPatrolStrategy::ExecuteStrategy(AEnemy* Enemy, float DeltaTime)
{
	if (!Enemy || DeltaTime <= 0.f)
	{
		return;
	}

	TimeToChange -= DeltaTime;
	if (TimeToChange <= 0.f || Direction.IsNearlyZero())
	{
		PickNewDirection();
	}

	TimeToMine -= DeltaTime;
	if (TimeToMine <= 0.f)
	{
		Enemy->DropMine();
		TimeToMine = MineInterval;
	}

	// Desplazamiento directo con barrido de colisi車n (bSweep = true)
	const FVector CurrentLocation = Enemy->GetActorLocation();
	const FVector NextLocation = CurrentLocation + (Direction * PatrolSpeed * DeltaTime);
	Enemy->SetActorLocation(NextLocation, true);

	// Orienta la malla/actor suavemente hacia la direcci車n de movimiento
	if (!Direction.IsNearlyZero())
	{
		const FRotator TargetRot = Direction.Rotation();
		Enemy->SetActorRotation(FMath::RInterpTo(Enemy->GetActorRotation(), TargetRot, DeltaTime, 8.f));
	}
}