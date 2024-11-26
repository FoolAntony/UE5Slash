// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CharacterTypes.h"
#include "PlayerCharacter.generated.h"


class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class AItem;
class UAnimMontage;
class AWeapon;


UCLASS()
class UE5SLASH_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;

	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	*	Enhanced input action variables
	*/
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* GContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MovementAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InteractAction;	
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AttackAction;

	/*
	*	Enhanced action functions
	*/
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact();
	void Attack();

	/*
	*	Play montage functions
	*/
	void PlayAttackMontage();
	void PlayEquipMontage(FName SectionName);

	UFUNCTION(BlueprintCallable)
	void AttackEnd();
	bool CanAttack();
	bool CanDisarm();
	bool CanArm();

	UFUNCTION(BlueprintCallable)
	void Disarm();
	
	UFUNCTION(BlueprintCallable)
	void Arm();
	
	UFUNCTION(BlueprintCallable)
	void FinishEquipping();

private:

	/*
	*	Player states
	*/
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
	EActionState ActionState = EActionState::EAS_Unoccupied;

	/*
	*	Player character actor components
	*/
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, Category = "Hairs")
	UGroomComponent* Hair;

	UPROPERTY(VisibleAnywhere, Category = "Hairs")
	UGroomComponent* Eyebrows;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	AWeapon* EquippedWeapon;
	
	/*
	*	Animation montages
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* AttackMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* EquipMontage;

public:

	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
};
