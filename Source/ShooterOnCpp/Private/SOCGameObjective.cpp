// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCGameObjective.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ShooterOnCppCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASOCGameObjective::ASOCGameObjective()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);

	SetReplicates(true);

}

// Called when the game starts or when spawned
void ASOCGameObjective::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASOCGameObjective::PlayEffects()
{
	if (PickupFx) 
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, PickupFx, GetActorLocation());
	}
	
}

void ASOCGameObjective::PlaySound()
{
	if (PickUpSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PickUpSound, GetActorLocation());
	}
}

// Called every frame
void ASOCGameObjective::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASOCGameObjective::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	PlayEffects();
	PlaySound();

	if(Role == ROLE_Authority)
	{
		AShooterOnCppCharacter* SOCChar = Cast<AShooterOnCppCharacter>(OtherActor);
		if (SOCChar)
		{
			
			SOCChar->bIsCarryingObjective = true;
			Destroy();
		}

	}


}

