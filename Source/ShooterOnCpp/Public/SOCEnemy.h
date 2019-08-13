// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SOCEnemy.generated.h"

UCLASS()
class SHOOTERONCPP_API ASOCEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASOCEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Components)
	class UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnSeenPawn(APawn* SeenPawn);

	FRotator OriginalRotation;

	UFUNCTION()
	void OnNoiseHeard(APawn* HeardPawn, const FVector& Location, float Volume);

	UFUNCTION()
	void ResetRotation();

	FTimerHandle TimerHandle_ResetOrientation;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
