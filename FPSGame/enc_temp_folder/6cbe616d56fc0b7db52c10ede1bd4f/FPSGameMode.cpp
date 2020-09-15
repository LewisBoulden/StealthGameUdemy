// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn)
{
	if (InstigatorPawn == nullptr)
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Succesfully Extracted Item"));

	//This is not great as we are just assuming the first player controller is set but fine for now.
	InstigatorPawn->DisableInput(GetWorld()->GetFirstPlayerController());

	OnMissionCompleted(InstigatorPawn);

	auto PlayerController = Cast<APlayerController>(InstigatorPawn->GetController());
	if (PlayerController != nullptr)
	{
		//TODO jth: all this is totally hackey as it's making assumptions about the actor we want being the first instance
		TArray<AActor*> ReturnedActors;
		UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

		if (ReturnedActors.Num() > 0)
		{
			auto NewViewTarget = ReturnedActors[0];
			PlayerController->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_EaseInOut, 0.6f);
		}
	}
}
