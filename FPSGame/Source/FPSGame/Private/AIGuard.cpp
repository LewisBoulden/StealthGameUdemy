// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGuard.h"
#include "Perception/PawnSensingComponent.h"


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
}


void AAIGuard::HandleSeePlayer(APawn* PawnInstigator)
{
	if (PawnInstigator != nullptr)
	{
		UE_LOG(LogActorComponent, Warning, TEXT("The guard has seen the moving %s player"), *PawnInstigator->GetName());
	}
}

