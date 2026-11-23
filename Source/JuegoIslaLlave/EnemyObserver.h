#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyObserver.generated.h"

class AEnemy;

UINTERFACE(MinimalAPI)
class UEnemyObserver : public UInterface
{
	GENERATED_BODY()
};

class JUEGOISLALLAVE_API IEnemyObserver
{
	GENERATED_BODY()
public:
	virtual void OnPlayerDetected(AEnemy* Source) = 0;
};
