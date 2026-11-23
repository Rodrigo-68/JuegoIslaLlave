#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnemyInterface.h"
#include "PatrolStrategy.generated.h"

class AEnemy;

UCLASS()
class JUEGOISLALLAVE_API UPatrolStrategy : public UObject, public IEnemyInterface
{
	GENERATED_BODY()

public:
	UPatrolStrategy();

	virtual void ExecuteStrategy(AEnemy* Enemy, float DeltaTime) override;

	void ResetPatrol();

private:
	void PickNewDirection();

	FVector Direction;
	float PatrolSpeed = 200.f;
	float TimeToChange = 0.f;
	float TimeToMine = 2.f;
	float MineInterval = 2.f;
};