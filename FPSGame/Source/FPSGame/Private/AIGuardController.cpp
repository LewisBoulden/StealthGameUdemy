// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGuardController.h"
#include "Engine/TargetPoint.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"

AAIGuardController::AAIGuardController()
{
}

void AAIGuardController::BeginPlay()
{
    Super::BeginPlay();

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);

    GoToRandomWaypoint();
}

void AAIGuardController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);

    GetWorldTimerManager().ClearTimer(TimerHandle_AIGuardWaitTimerHandle);
    GetWorldTimerManager().SetTimer(TimerHandle_AIGuardWaitTimerHandle, this, &AAIGuardController::GoToRandomWaypoint, 3.f);
}

void AAIGuardController::PauseMove()
{
    Super::PauseMove(GetCurrentMoveRequestID());

    GetWorldTimerManager().ClearTimer(TimerHandle_AIGuardMovePauseWaitTimeHandle);
    GetWorldTimerManager().SetTimer(TimerHandle_AIGuardMovePauseWaitTimeHandle, this, &AAIGuardController::ResumeMove, 2.f);
}

void AAIGuardController::ResumeMove()
{
    Super::ResumeMove(GetCurrentMoveRequestID());
}

ATargetPoint* AAIGuardController::GetRandomWaypoint()
{
    const auto Index = FMath::RandRange(0, Waypoints.Num() - 1);
    return Cast<ATargetPoint>(Waypoints[Index]);
}

void AAIGuardController::GoToRandomWaypoint()
{
    const auto NextTargetWaypoint = GetRandomWaypoint();
    if (NextTargetWaypoint != nullptr)
    {
        MoveToActor(NextTargetWaypoint);
    }
}
