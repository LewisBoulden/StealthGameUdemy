// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"


#include "EngineUtils.h"
#include "FPSCharacter.h"
#include "FPSPlayerController.h"
#include "Engine/World.h"

void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, const EGameCompletionState State)
{
    // using C++11 style ranged loop doesn't seem to be supported for this FConstPlayerControllerIterator type
    for (FConstPlayerControllerIterator Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
    {
        auto FPSPlayerController = Cast<AFPSPlayerController>(Iter->Get());
        if (FPSPlayerController != nullptr && FPSPlayerController->IsLocalController())
        {
            // disable all player controlled pawn input if the game is completed
            auto PlayerPawn = FPSPlayerController->GetPawn();
            if (PlayerPawn != nullptr && PlayerPawn->IsLocallyControlled())
            {
                PlayerPawn->DisableInput(nullptr);
            }

            // complete the mission
            FPSPlayerController->OnMissionCompleted(InstigatorPawn, State);
        }
    }
}
