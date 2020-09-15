// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPad.h"
#include "FPSCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ALaunchPad::ALaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetRelativeScale3D(FVector(200.f, 200.f, 50.f));
	RootComponent = MeshComponent;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxOverlapComp"));
	OverlapComp->SetBoxExtent(FVector(200.f, 200.f, 200.f));
	OverlapComp->SetupAttachment(RootComponent);

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

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::HandleLaunchOverlappingActor);
	
}

void ALaunchPad::HandleLaunchOverlappingActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		//do the work here to launch the player and the blue boxes.
		//todo jth: fix the projectile that's no longer launching.

        auto OverlappingPlayer = Cast<AFPSCharacter>(OtherActor);
        if (OverlappingPlayer == nullptr)
        {
            return;
        }

		//This is currently not launching the player as expected
		OverlappingPlayer->LaunchCharacter(LaunchVelocity, false, false);
	}

	//todo jth: do the work to launch the boxes
}

