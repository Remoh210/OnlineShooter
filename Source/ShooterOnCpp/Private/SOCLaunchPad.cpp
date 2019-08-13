// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCLaunchPad.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "ShooterOnCppCharacter.h"
#include "kismet/GameplayStatics.h"

// Sets default values
ASOCLaunchPad::ASOCLaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	//MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	//BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//BoxComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ASOCLaunchPad::HandleOverlap);
	
	BoxComp->SetupAttachment(MeshComp);
	
	LaunchForce = 1000.f;
	LaunchAngle = 45.0f;
	
}

void ASOCLaunchPad::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult & SweepResult)
{	
	FRotator LaunchDir = GetActorRotation();
	LaunchDir.Pitch += LaunchAngle;
	FVector JumpDirection = LaunchDir.Vector() * LaunchForce;

	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("Collision With Primitive"));
		Character->LaunchCharacter(JumpDirection, true, true);
	}
	else if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		UE_LOG(LogTemp, Warning, TEXT("Collision With Primitive"));
		OtherComp->AddImpulse(JumpDirection, NAME_None, true);
	}
	
	PlayEffects();
	PlaySound();
}

// Called when the game starts or when spawned
void ASOCLaunchPad::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASOCLaunchPad::PlayEffects()
{
	if (LaunchFx)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchFx, GetActorLocation());
	}
}

void ASOCLaunchPad::PlaySound()
{
	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

// Called every frame
void ASOCLaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

