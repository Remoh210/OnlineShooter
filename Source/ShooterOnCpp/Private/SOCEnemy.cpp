// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCEnemy.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "ShooterOnCppGameMode.h"
#include "NavigationSystem.h"
#include "Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"



// Sets default values
ASOCEnemy::ASOCEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateAbstractDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing Component"));

	PawnSensingComp->OnSeePawn.AddDynamic(this, &ASOCEnemy::OnSeenPawn);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &ASOCEnemy::OnNoiseHeard);

	OriginalRotation = GetActorRotation();

	GuardState = EAIState::Idle;

	NavigationArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

}

// Called when the game starts or when spawned
void ASOCEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	//UE_LOG(LogTemp, Warning, TEXT("Begin"));
	if (bPatrol)
	{
		//UE_LOG(LogTemp, Warning, TEXT("StartPatrol"));
		//MoveToNextPatrolPont();
	}
	
}

void ASOCEnemy::OnSeenPawn(APawn * SeenPawn)
{

	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 5.0f);

	AShooterOnCppGameMode* GM = Cast<AShooterOnCppGameMode>(GetWorld()->GetAuthGameMode());

	SetGuardState(EAIState::Alerted);
	if (GM)
	{
		GM->CompleteMission(SeenPawn, false);
	}

	GetController()->StopMovement();

}

void ASOCEnemy::MoveToNextPatrolPont()
{
	if (CurrentPatrolPoint == nullptr || CurrentPatrolPoint == SecondPatrolPoint)
	{
		CurrentPatrolPoint = FirstControlPoint;
		UE_LOG(LogTemp, Warning, TEXT("A"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("B"));
		CurrentPatrolPoint = SecondPatrolPoint;
	}

	UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), CurrentPatrolPoint);
}

void ASOCEnemy::OnNoiseHeard(APawn * HeardPawn, const FVector & Location, float Volume)
{
	if(GuardState == EAIState::Alerted)
	{
		return;
	}

	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 5.0f);

	FVector Direction = Location - GetActorLocation();

	FRotator LookAt = FRotationMatrix::MakeFromX(Direction).Rotator();

	LookAt.Pitch = 0.f;
	LookAt.Roll = 0.f;
	SetActorRotation(LookAt);

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &ASOCEnemy::ResetRotation, 3.f);


	SetGuardState(EAIState::Suspicios);
	//GetController()->StopMovement();
	

}

void ASOCEnemy::ResetRotation()
{
	if (GuardState == EAIState::Alerted)
	{
		return;
	}
	SetActorRotation(OriginalRotation);
	SetGuardState(EAIState::Idle);

	//if (bPatrol)
	//{
	//	MoveToNextPatrolPont();
	//}
}

void ASOCEnemy::SetGuardState(EAIState NewState)
{
	if (GuardState == NewState)
	{
		return;
	}

	GuardState = NewState;

	OnStateChanged(GuardState);
}



// Called every frame
void ASOCEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (CurrentPatrolPoint)
	//{
	//	FVector Delta = CurrentPatrolPoint->GetActorLocation() - GetActorLocation();
	//	float dist = Delta.Size();

	//	if (dist < 50.f)
	//	{
	//		//MoveToNextPatrolPont();
	//	}
	//}
}



