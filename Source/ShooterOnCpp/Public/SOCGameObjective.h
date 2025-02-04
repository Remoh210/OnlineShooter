// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SOCGameObjective.generated.h"

UCLASS()
class SHOOTERONCPP_API ASOCGameObjective : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASOCGameObjective();
	

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	class UParticleSystem* PickupFx;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	class USoundBase* PickUpSound;
	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void PlayEffects();
	void PlaySound();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
