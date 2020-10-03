// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPad.h"
#include "FPSCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ALaunchPad::ALaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxOverlapComp"));
	OverlapComp->SetBoxExtent(FVector(75.f, 75.f, 50.f));
	RootComponent = OverlapComp;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComponent->SetupAttachment(RootComponent);

	ArrowMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMeshComponent"));
	ArrowMeshComponent->SetupAttachment(RootComponent);
}


// Called every frame
void ALaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//We may not even need this method for this class
}


// Called when the game starts or when spawned
void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();

	if (OverlapComp == nullptr)
	{
		UE_LOG(LogActor, Error, TEXT("Overlap Component not set on the LaunchPad."));
	}
	
	if (MeshComponent == nullptr)
	{
		UE_LOG(LogActor, Error, TEXT("Static Mesh Component not set on the LaunchPad."));
	}
	
	if (ArrowMeshComponent == nullptr)
	{
		UE_LOG(LogActor, Error, TEXT("Static Arrow Mesh Component not set on the LaunchPad."));
	}
	
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::HandleLaunchOverlappingActor);
}

void ALaunchPad::HandleLaunchOverlappingActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	auto LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch += LaunchPitchAngle;
	const auto LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;
	
	if (OtherActor != nullptr)
	{
        auto OverlappingPlayer = Cast<AFPSCharacter>(OtherActor);
        if (OverlappingPlayer == nullptr)
        {
            return;
        }

		//This is currently not launching the player as expected
		OverlappingPlayer->LaunchCharacter(LaunchVelocity, false, false);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchPadEffect, GetActorLocation());
	}

	if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		//This is currently not launching the player as expected
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchPadEffect, GetActorLocation());
	}
}

