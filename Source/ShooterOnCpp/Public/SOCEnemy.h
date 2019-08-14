// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SOCEnemy.generated.h"

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,
	Suspicios,
	Alerted
};

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

	UPROPERTY(EditInstanceOnly, Category = AI)
	bool bPatrol;

	
	//UPROPERTY(EditInstanceOnly, Category = AI, meta = (EditCondition = "bPatrol")
	UPROPERTY(EditInstanceOnly, Category = AI, meta = (EditCondition = "bPatrol"))
	AActor* FirstControlPoint;

	UPROPERTY(EditInstanceOnly, Category = AI, meta = (EditCondition = "bPatrol"))
	AActor* SecondPatrolPoint;

	AActor* CurrentPatrolPoint;

	class UNavigationSystemV1* NavigationArea;

	UFUNCTION()
	void OnSeenPawn(APawn* SeenPawn);

	void MoveToNextPatrolPont();

	FRotator OriginalRotation;

	UFUNCTION()
	void OnNoiseHeard(APawn* HeardPawn, const FVector& Location, float Volume);

	UFUNCTION()
	void ResetRotation();

	FTimerHandle TimerHandle_ResetOrientation;

	EAIState GuardState;

	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent)
	void OnStateChanged(EAIState NewState);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
