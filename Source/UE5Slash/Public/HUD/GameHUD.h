// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

class UPlayerOverlay;

UCLASS()
class UE5SLASH_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	FORCEINLINE UPlayerOverlay* GetPlayerOverlay() const { return PlayerOverlay; }

protected:
	virtual void BeginPlay() override;
	
private:

	UPROPERTY(EditDefaultsOnly, Category = "PlayerHUD")
	TSubclassOf<UPlayerOverlay> PlayerOverlayClass;

	UPROPERTY()
	UPlayerOverlay* PlayerOverlay;

};
