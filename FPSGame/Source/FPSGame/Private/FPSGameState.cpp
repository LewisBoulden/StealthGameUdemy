// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"


#include "EngineUtils.h"
#include "FPSCharacter.h"

void AFPSGameState::MulticastOnMissionComplete_Implementation(AActor* InstigatorPawn, const EGameCompletionState State)
{
    // don't use GetPawnIterator as it's deprecated for 4.26
    for (auto Character : TActorRange<AFPSCharacter>(GetWorld()))
    {
        if (Character->IsLocallyControlled())
        {
            Character->DisableInput(nullptr);
        }
    }
}
