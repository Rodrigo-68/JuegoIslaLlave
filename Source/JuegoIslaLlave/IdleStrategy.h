#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnemyInterface.h"
#include "IdleStrategy.generated.h"

class AEnemy;

UCLASS()
class JUEGOISLALLAVE_API UIdleStrategy : public UObject, public IEnemyInterface
{
	GENERATED_BODY()

public:
	UIdleStrategy();

	virtual void ExecuteStrategy(AEnemy* Enemy, float DeltaTime) override;

	void OnEnterIdle(AEnemy* Enemy);

private:
	float TurnSpeed = 120.f; // Grados por segundo al dar vueltas
};