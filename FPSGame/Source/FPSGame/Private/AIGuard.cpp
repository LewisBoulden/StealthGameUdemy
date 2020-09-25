// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGuard.h"

#include <stdbool.h>

#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "FPSGameMode.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AAIGuard::AAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GuardSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	GuardSensingComp->bHearNoises = true;
	GuardSensingComp->bSeePawns = true;
	GuardSensingComp->bOnlySensePlayers = true;

}

// Called every frame
void AAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AAIGuard::BeginPlay()
{
	Super::BeginPlay();

	//The rotation to return to after the timer has expired
	OriginRotation = GetActorRotation();

	//Bind up the sensing callbacks
	GuardSensingComp->OnSeePawn.AddDynamic(this, &AAIGuard::HandleSeePlayer);
	GuardSensingComp->OnHearNoise.AddDynamic(this, &AAIGuard::HandleHearNoise);
}


void AAIGuard::HandleSeePlayer(APawn* PawnInstigator)
{
	if (PawnInstigator == nullptr)
	{
		return;
	}

	UE_LOG(LogActor, Warning, TEXT("AI Guard saw the %s"), *PawnInstigator->GetName());
		
	//Some debug code to display where the player was seen by AI
	DrawDebugSphere(GetWorld(), PawnInstigator->GetActorLocation(), 32.f, 12, FColor::Purple, false, 10);

	auto GameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode != nullptr)
	{
		GameMode->CompleteMission(PawnInstigator, GameCompletionState::Failed);	
	}
}

void AAIGuard::HandleHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	auto Direction = Location - GetActorLocation();
	Direction.Normalize();
	
	auto NewLookAtLocation = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAtLocation.Pitch = 0.0f;
	NewLookAtLocation.Roll = 0.0f;
	
	SetActorRotation(NewLookAtLocation);

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AAIGuard::ResetGuardRotation, 3.f);
}

void AAIGuard::ResetGuardRotation()
{
	SetActorRotation(OriginRotation);
}

