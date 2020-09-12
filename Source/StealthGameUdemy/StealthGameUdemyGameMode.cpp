// Copyright Epic Games, Inc. All Rights Reserved.

#include "StealthGameUdemyGameMode.h"
#include "StealthGameUdemyHUD.h"
#include "StealthGameUdemyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStealthGameUdemyGameMode::AStealthGameUdemyGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AStealthGameUdemyHUD::StaticClass();
}
