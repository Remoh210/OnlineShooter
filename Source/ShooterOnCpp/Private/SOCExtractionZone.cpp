// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterOnCppCharacter.h"
#include "ShooterOnCppGameMode.h"


// Sets default values
ASOCExtractionZone::ASOCExtractionZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));


	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(20.f));
	RootComponent = OverlapComp;

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ASOCExtractionZone::HandleOverlap);

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));

	DecalComp->DecalSize = FVector(200.f, 200.f, 200.f);
	DecalComp->AttachTo(RootComponent);
}



void ASOCExtractionZone::HandleOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, 
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{


	AShooterOnCppCharacter* pawn = Cast<AShooterOnCppCharacter>(OtherActor);

	if (!pawn)
	{
		return;
	}
	if(pawn->bIsCarryingObjective)
	{
		 AShooterOnCppGameMode* GM = Cast<AShooterOnCppGameMode>(GetWorld()->GetAuthGameMode());
		 if (GM)
		 {
			 GM->CompleteMission(pawn, true);
		 }
	}
	else
	{
		UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
	}

}
