// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Engine/World.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"


// Sets default values
AExtractionZone::AExtractionZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.f));
	RootComponent = OverlapComp;

	//Temp till there's a mesh or effect is added.
	OverlapComp->SetHiddenInGame(false); //Shows the bounds of the componenet

	ExtractionDecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("ExtractionDecalComp"));
	ExtractionDecalComp->DecalSize = OverlapComp->GetScaledBoxExtent();
	ExtractionDecalComp->SetupAttachment(OverlapComp);
}


// Called when the game starts or when spawned
void AExtractionZone::BeginPlay()
{
	Super::BeginPlay();
	
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AExtractionZone::HandleExtractionOverlap);

}

void AExtractionZone::HandleExtractionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	auto OverlappingPlayer = Cast<AFPSCharacter>(OtherActor);
	if (OverlappingPlayer == nullptr)
	{
		return;
	}

	if (OverlappingPlayer->bIsHoldingObjective)
	{
		UE_LOG(LogTemp, Log, TEXT("Succesfully Extracted Item"));

		//This code will not work on a server/client setup
		auto GameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode != nullptr)
		{
			const auto bWasSuccess = true;
			GameMode->CompleteMission(OverlappingPlayer, GameCompletionState::Success);
		}
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ObjectiveMissingSound, this->GetActorLocation());
	}
}
