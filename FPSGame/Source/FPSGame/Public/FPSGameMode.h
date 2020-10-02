// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UENUM(BlueprintType, Category="GameState")
enum class EGameCompletionState : uint8
{
    Success,
    Failed
};

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AFPSGameMode();

	void CompleteMission(APawn* InstigatorPawn, const EGameCompletionState State);

	UFUNCTION(BlueprintImplementableEvent, Category="GameMode")
	void OnMissionCompleted(APawn* InstigatorPawn, const EGameCompletionState State);
	

protected:

	UPROPERTY(EditDefaultsOnly, Category="Spectating")
	TSubclassOf<AActor> SpectatingViewpointClass;

};



