// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCObjective.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ShooterOnCppCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASOCObjective::ASOCObjective()
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
void ASOCObjective::BeginPlay()
{
	Super::BeginPlay();
	
	PlayEffects();
}

void ASOCObjective::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFx, GetActorLocation());

}

// Called every frame
void ASOCObjective::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASOCObjective::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	PlayEffects();
	AShooterOnCppCharacter* SOCChar = Cast<AShooterOnCppCharacter>(OtherActor);

	if (SOCChar)
	{
		switch (AmmoType)
		{
		case EAmmoType::AE_Fire:
			SOCChar->ProjectileType = EProjectileType::PE_Fire;
			break;
		case EAmmoType::AE_Bolt:
			SOCChar->ProjectileType = EProjectileType::PE_Bolt;
			break;
		case EAmmoType::AE_else:
			SOCChar->ProjectileType = EProjectileType::PE_Fire;
			break;
		default:
			SOCChar->ProjectileType = EProjectileType::PE_Fire;
			break;
		}
		
	}

}

