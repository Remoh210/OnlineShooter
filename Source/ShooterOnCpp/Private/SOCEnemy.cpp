// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCEnemy.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "ShooterOnCppGameMode.h"

// Sets default values
ASOCEnemy::ASOCEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateAbstractDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing Component"));

	PawnSensingComp->OnSeePawn.AddDynamic(this, &ASOCEnemy::OnSeenPawn);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &ASOCEnemy::OnNoiseHeard);

	OriginalRotation = GetActorRotation();

}

// Called when the game starts or when spawned
void ASOCEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASOCEnemy::OnSeenPawn(APawn * SeenPawn)
{

	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 5.0f);

	AShooterOnCppGameMode* GM = Cast<AShooterOnCppGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->CompleteMission(SeenPawn, false);
	}

}

void ASOCEnemy::OnNoiseHeard(APawn * HeardPawn, const FVector & Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 5.0f);

	FVector Direction = Location - GetActorLocation();

	FRotator LookAt = FRotationMatrix::MakeFromX(Direction).Rotator();

	LookAt.Pitch = 0.f;
	LookAt.Roll = 0.f;
	SetActorRotation(LookAt);

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &ASOCEnemy::ResetRotation, 3.f);

}

void ASOCEnemy::ResetRotation()
{
	SetActorRotation(OriginalRotation);
}

// Called every frame
void ASOCEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



