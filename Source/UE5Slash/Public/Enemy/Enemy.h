// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Characters/CharacterTypes.h"
#include "Enemy.generated.h"

class UHealthBarComponent;
class AAIController;
class UPawnSensingComponent;

UCLASS()
class UE5SLASH_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:

	AEnemy();
	virtual void Tick(float DeltaTime) override;
	void CheckPatrolTarget();
	void CheckCombatTarget();

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)  override;

	virtual void Destroyed() override;
protected:

	virtual void BeginPlay() override;
	virtual void Attack() override;
	virtual void HandleDamage(float DamageAmount) override;
	virtual void Die() override;
	bool InTargetRange(AActor* Target, double Radious);
	void MoveToTarget(AActor* Target);
	virtual int32 PlayDeathMontage() override;

	UPROPERTY(EditAnywhere, Category = Combat)
	float DeathLifeSpan = 8.0;

	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);

	AActor* ChoosePatrolTarget();


	UPROPERTY(BlueprintReadOnly)
	EDeathPose DeathPose;

	UPROPERTY(BlueprintReadOnly)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;

	virtual bool CanAttack() override;

	virtual void AttackEnd() override;

private:	
	UPROPERTY(EditAnywhere, Category = Combat)
	float EnemySpeedWalk = 125.f;
	UPROPERTY(EditAnywhere, Category = Combat)
	float EnemySpeedChase = 300.f;


	/*
	*  Components
	*/
	

	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWeapon> WeaponClass;

	UPROPERTY()
	AActor* CombatTarget;

	UPROPERTY(EditAnywhere)
	double CombatRadius = 500.f;
	
	UPROPERTY(EditAnywhere)
	double AttackRadius = 150.f;

	/*
	*	Navigation
	*/

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	UPROPERTY()
	AAIController* EnemyController;

	UPROPERTY(EditAnywhere)
	double PatrolRadius = 200.f;

	FTimerHandle PatrolTimer;

	void PatrolTimerFinished();

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float WaitMin = 5.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float WaitMax = 10.f;

	/*AI Behaviour*/

	void HideHealthBar();
	void ShowHealthBar();
	void LoseInterest();
	void StartPatrolling();
	void ChaseTarget();
	void ClearPatrolTimer();
	bool IsOutsideCombatRadius();
	bool IsOutsideAttackRadius();
	bool IsInsideAttackRadius();
	bool IsPatrolling();
	bool IsChasing();
	bool IsAttacking();
	bool IsDead();
	bool IsEngaged();


	/* Combat */

	void StartAttackTimer();
	void ClearAttackTimer();

	FTimerHandle AttackTimer;
	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMin = 3.f;
	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMax = 4.f;

};
