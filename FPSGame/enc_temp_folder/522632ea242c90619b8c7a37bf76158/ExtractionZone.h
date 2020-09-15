// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExtractionZone.generated.h"

class UBoxComponent;
class UDecalComponent;
class USoundBase;

UCLASS()
class FPSGAME_API AExtractionZone final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	explicit AExtractionZone();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void HandleExtractionOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult& SweepResult);

protected:

	UPROPERTY(VisibleAnywhere, Category="Componenets")
	UBoxComponent* OverlapComp;
	
	UPROPERTY(VisibleAnywhere, Category="Componenets")
	UDecalComponent* ExtractionDecalComp;

	UPROPERTY(VisibleAnywhere, Category="Sounds")
	USoundBase* ObjectiveMissingSound;
};
