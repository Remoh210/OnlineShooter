// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SOCLaunchPad.generated.h"

UCLASS()
class SHOOTERONCPP_API ASOCLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASOCLaunchPad();

protected:

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult & SweepResult);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = GamePlay)
	float LaunchForce;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float LaunchAngle;

	UPROPERTY(VisibleAnywhere, Category = Components)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = Components)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	class UParticleSystem* LaunchFx;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	class USoundBase* LaunchSound;

	void PlayEffects();
	void PlaySound();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
