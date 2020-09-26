// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "AIGuardController.h"
#include "WidgetComponent.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"

#include "AIGuard.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIGuardState : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Suspicious	UMETA(DisplayName = "Suspicious"),	
	Alert		UMETA(DisplayName = "Alert"),
};

UCLASS()
class FPSGAME_API AAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIGuard();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category="AI | Guard")
	void OnGuardStateChanged(EAIGuardState NewState);

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
	
	void SetGuardState(EAIGuardState NewState);

	void PausePatrol() const;
protected:
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	UPawnSensingComponent* GuardSensingComp;

private:
	FRotator OriginRotation;

	FTimerHandle TimerHandle_ResetOrientation;

	EAIGuardState GuardState;
};
