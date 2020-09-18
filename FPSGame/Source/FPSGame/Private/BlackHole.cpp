// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    MeshComponent->SetRelativeScale3D(FVector(6.f, 6.f, 6.f));
	RootComponent = MeshComponent;

	SuctionSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SuctionSphereComponent"));
	SuctionSphereComponent->SetSphereRadius(SuctionSphereDefaultRadius);
	SuctionSphereComponent->SetupAttachment(MeshComponent);

	DestructionSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("DestructionSphereComponent"));
	DestructionSphereComponent->SetSphereRadius(DestructionSphereDefaultRadius);
	DestructionSphereComponent->SetupAttachment(MeshComponent);
}


// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    HandleBlackholeSuction();
}


// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
    Super::BeginPlay();

    DestructionSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapDestructionSphere);
}


bool ABlackHole::GetOverlappingComps(const USphereComponent& Comp)
{
    OverlappingComps.Empty();
    SuctionSphereComponent->GetOverlappingComponents(OverlappingComps);
    
    return (OverlappingComps.Num() > 0) ? true : false;
}


void ABlackHole::HandleBlackholeSuction()
{
    auto AreCompsOverlapping = GetOverlappingComps(*SuctionSphereComponent);
    if (AreCompsOverlapping == true)
    {
        for (const auto attractedComponenet : OverlappingComps)
        {
            if (attractedComponenet != nullptr && attractedComponenet->IsSimulatingPhysics())
            {
                attractedComponenet->AddRadialForce(
                    GetActorLocation(),
                    SuctionRadius,
                    SuctionStrength,
                    ERadialImpulseFalloff::RIF_Linear
                );
            }
        }
    }
}

void ABlackHole::OverlapDestructionSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor != nullptr)
    {
        OtherActor->Destroy();
    }
}

