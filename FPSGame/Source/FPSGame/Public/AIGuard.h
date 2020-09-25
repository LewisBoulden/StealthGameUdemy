// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"

#include "AIGuard.generated.h"

class UPawnSensingComponent;

UCLASS()
class FPSGAME_API AAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIGuard();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void HandleSeePlayer(APawn* PawnInstigator);
	
	UFUNCTION()
	void HandleHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);

	UFUNCTION()
	void ResetGuardRotation();
	
protected:
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	UPawnSensingComponent* GuardSensingComp;

private:
	FRotator OriginRotation;

	FTimerHandle TimerHandle_ResetOrientation;
};
