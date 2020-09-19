// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class FPSGAME_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleLaunchOverlappingActor(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult& SweepResult);

protected:

	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* ArrowMeshComponent;
	
    UPROPERTY(VisibleAnywhere, Category="Components")
    UBoxComponent* OverlapComp;

    UPROPERTY(EditDefaultsOnly, Category="Components")
	UParticleSystem* LaunchPadEffect;

	UPROPERTY(EditInstanceOnly, Category="Gameplay")
	float LaunchStrength = 1500.f;
	
    UPROPERTY(EditInstanceOnly, Category="Gameplay")
    float LaunchPitchAngle = 35.f;

};
