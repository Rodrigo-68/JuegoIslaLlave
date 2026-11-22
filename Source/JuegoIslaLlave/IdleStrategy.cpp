#include "IdleStrategy.h"
#include "Enemy.h"

UIdleStrategy::UIdleStrategy()
	: TurnSpeed(120.f)
{
}

void UIdleStrategy::OnEnterIdle(AEnemy* Enemy)
{
	if (!Enemy)
	{
		return;
	}

	// Cambia el color al entrar en estado Idle (ej. verde)
	Enemy->SetEnemyColor(FLinearColor::Green);
}

void UIdleStrategy::ExecuteStrategy(AEnemy* Enemy, float DeltaTime)
{
	if (!Enemy || DeltaTime <= 0.f)
	{
		return;
	}

	// 1. Dar vueltas sobre su eje vertical (Yaw)
	Enemy->AddActorLocalRotation(FRotator(0.f, TurnSpeed * DeltaTime, 0.f));

	// 2. Si estando en Idle detecta al jugador, se duplica y vuelve a patrullar
	if (Enemy->IsPlayerDetected())
	{
		Enemy->TryDuplicateFromIdle();
		Enemy->SwitchToPatrol();
	}
}