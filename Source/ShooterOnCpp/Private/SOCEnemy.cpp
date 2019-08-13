// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCEnemy.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASOCEnemy::ASOCEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateAbstractDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing Component"));

	PawnSensingComp->OnSeePawn.AddDynamic(this, &ASOCEnemy::OnSeenPawn);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &ASOCEnemy::OnNoiseHeard);

}

// Called when the game starts or when spawned
void ASOCEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASOCEnemy::OnSeenPawn(APawn * SeenPawn)
{

	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 5.0f);

}

void ASOCEnemy::OnNoiseHeard(APawn * HeardPawn, const FVector & Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 5.0f);

	UE_LOG(LogTemp, Warning, TEXT("HEAAAAAAAAAAAAAAAAAARFFF"));
}

// Called every frame
void ASOCEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



