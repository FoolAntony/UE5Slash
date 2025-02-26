// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
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
class UPlayerOverlay;


UCLASS()
class UE5SLASH_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:

	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)  override;

	virtual void Jump() override;



protected:

	virtual void BeginPlay() override;

	/**	Enhanced action functions */
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact();
	virtual void Attack() override;

	/** Combat */
	void PlayEquipMontage(const FName& SectionName);
	virtual void AttackEnd() override;
	virtual bool CanAttack() override;
	virtual void Die() override;
	bool CanDisarm();
	bool CanArm();
	void Disarm();
	void Arm();

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToBack();

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToHand();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();	
	
	UFUNCTION(BlueprintCallable)
	void HitReactEnd();

	/**	Enhanced input action variables */
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

private:

	void InitializePlayerOverlay();
	void SetPlayerHUDHealth();
	bool IsUnoccupied();

	/**	Player States */
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
	EActionState ActionState = EActionState::EAS_Unoccupied;

	/**	Character Components*/
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
	
	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* EquipMontage;

	UPROPERTY()
	UPlayerOverlay* PlayerOverlay;

public:

	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	FORCEINLINE EActionState GetActionState() const { return ActionState; }
};
