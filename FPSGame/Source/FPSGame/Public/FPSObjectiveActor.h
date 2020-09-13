// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UParticleSystem;

UCLASS()
class FPSGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

	//AActor overloads
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PlayEffects();

protected:

	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category="Components")
	USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, Category="FX")
	UParticleSystem* PickupFX;

};