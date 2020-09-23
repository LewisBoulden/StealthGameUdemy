// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGuard.h"

#include <stdbool.h>

#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
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
		
}

void AAIGuard::HandleHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	UE_LOG(LogActor, Warning, TEXT("AI Guard heard the %s"), *PawnInstigator->GetName());

	//Some debug code to just see that the AI guard is able to hear the player
	DrawDebugSphere(GetWorld(), Location, 32.f, 12, FColor::Red, false, 10);
}

