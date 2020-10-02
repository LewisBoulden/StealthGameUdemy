// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "FPSGameState.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	// use the custom GameState class
	GameStateClass = AFPSGameState::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, const EGameCompletionState State)
{
	if (InstigatorPawn == nullptr)
	{
		return;
	}

	//If the spectator viewport was set then we change the viewport to the spectator camera view
	if (SpectatingViewpointClass != nullptr)
	{
		auto PlayerController = Cast<APlayerController>(InstigatorPawn->GetController());
		if (PlayerController != nullptr)
		{
			//TODO jth: all this is totally hackey as it's making assumptions about the actor we want being the first instance
			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

			if (ReturnedActors.Num() > 0)
			{
				const auto NewViewTarget = ReturnedActors[0];
				PlayerController->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_EaseIn, 0.2f);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is nullptr. Please update GameMode Blueprint with valid subclass. Cannot change spectating  view target."));
	}

	//This is not great as we are just assuming the first player controller is set but fine for now.
	//InstigatorPawn->DisableInput(GetWorld()->GetFirstPlayerController());
	auto TheGameState = GetGameState<AFPSGameState>();
	if (TheGameState != nullptr)
	{
		TheGameState->MulticastOnMissionComplete(InstigatorPawn, State);	
	}
	

	OnMissionCompleted(InstigatorPawn, State);
}
