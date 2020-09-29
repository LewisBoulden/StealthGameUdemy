// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIGuardController.generated.h"

struct FTimerHandle;

class ATargetPoint;

/**
 * 
 */
UCLASS()
class FPSGAME_API AAIGuardController : public AAIController
{
	GENERATED_BODY()

public:

    explicit AAIGuardController();
    
    virtual void BeginPlay() override;

    virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

    void PauseMove();

private:
    void ResumeMove();    
    
private:
    UPROPERTY(EditAnywhere, Category="Waypoints")
    TArray<AActor*> Waypoints;

    UFUNCTION()
    ATargetPoint* GetRandomWaypoint();
    
    UFUNCTION()
    void GoToRandomWaypoint();

    FTimerHandle TimerHandle_AIGuardWaitTimerHandle;

    FTimerHandle TimerHandle_AIGuardMovePauseWaitTimeHandle;
};
