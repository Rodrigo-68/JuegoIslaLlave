#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ScriptInterface.h"
#include "EnemyInterface.h"
#include "Enemy.generated.h"

class UBoxComponent;
class USphereComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;
class UMaterialInstanceDynamic;
class UPatrolStrategy;
class UIdleStrategy;
class Amina;

UCLASS()
class JUEGOISLALLAVE_API AEnemy : public AActor
{
	GENERATED_BODY()

public:
	AEnemy();

	virtual void Tick(float DeltaTime) override;

	void SetStrategy(const TScriptInterface<IEnemyInterface>& NewStrategy);
	void SwitchToPatrol();
	void SwitchToIdle();

	void DropMine();
	void SetEnemyColor(const FLinearColor& NewColor);
	bool IsPlayerDetected() const;
	void TryDuplicateFromIdle();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDetectionBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void CheckPlayerProximity();
	void UpdateDetectionState(bool bDetected);

	//mina
	UPROPERTY()
	TArray<class Amina*> OwnedMines;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent* DetectionSphere;

	UPROPERTY()
	UMaterialInstanceDynamic* EnemyMaterial;

	UPROPERTY()
	UPatrolStrategy* PatrolStrategyObj;

	UPROPERTY()
	UIdleStrategy* IdleStrategyObj;

	UPROPERTY()
	TScriptInterface<IEnemyInterface> CurrentStrategy;

	UPROPERTY(EditAnywhere, Category = "AI|Detection")
	float DetectionRadius = 500.f;

	UPROPERTY(EditAnywhere, Category = "AI|Idle")
	float IdleTimeout = 10.f;





	UPROPERTY(EditAnywhere, Category = "AI|Duplication")
	float DuplicateCooldown = 2.f;

	static int32 TotalEnemyCount;

	float TimeWithoutDetection = 0.f;
	float DuplicateCooldownTimer = 0.f;
	bool bPlayerInRange = false;
	bool bIsInIdle = false;
};