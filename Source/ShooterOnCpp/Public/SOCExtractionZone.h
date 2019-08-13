// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SOCExtractionZone.generated.h"

UCLASS()
class SHOOTERONCPP_API ASOCExtractionZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASOCExtractionZone();

protected:

	UPROPERTY(VisibleAnywhere, Category = Components)
	class UBoxComponent* OverlapComp;

	UPROPERTY(VisibleAnywhere, Category = Components)
	class UDecalComponent* DecalComp;

	UPROPERTY(EditAnywhere, Category = Sounds)
	class USoundBase* ObjectiveMissingSound;

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


};
