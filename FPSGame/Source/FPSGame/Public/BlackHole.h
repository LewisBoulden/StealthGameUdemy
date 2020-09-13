// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "BlackHole.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class FPSGAME_API ABlackHole final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	explicit ABlackHole();

	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	bool GetOverlappingComps(const USphereComponent& Comp);
	void HandleBlackholeSuction();

	UFUNCTION()
	void OverlapDestructionSphere(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult& SweepResult);

protected:
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category="Components")
	USphereComponent* SuctionSphereComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	USphereComponent* DestructionSphereComponent;

	UPROPERTY(BlueprintReadWrite, Category="Gameplay")
    float SuctionSphereDefaultRadius = 3 * 1024.f;

	UPROPERTY(BlueprintReadWrite, Category="Gameplay")
    float DestructionSphereDefaultRadius = 20.f;

	UPROPERTY(BlueprintReadWrite, Category="Gameplay")
    float SuctionRadius = 3 * 1024.f;

	UPROPERTY(BlueprintReadWrite, Category="Gameplay")
    float SuctionStrength = 3 * -FMath::Pow(10, 6.5f);


private:
	TArray<UPrimitiveComponent*> OverlappingComps;

};
