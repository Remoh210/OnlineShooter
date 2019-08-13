// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	InnerSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComponent"));
	InnerSphereComp->SetSphereRadius(100);
	InnerSphereComp->SetupAttachment(MeshComp);

	InnerSphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapInnerSphere);

	OuterSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComponent"));
	OuterSphereComp->SetSphereRadius(3000);
	OuterSphereComp->SetupAttachment(MeshComp);

	lifeTime = 5.0f;
	count = 0.0f;
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

UFUNCTION()
void ABlackHole::OverlapInnerSphere(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{


}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OverlappedComponents;
	OuterSphereComp->GetOverlappingComponents(OverlappedComponents);

	//for (int32 i = 0; i < OverlappedComponents.Num(); i++)
	//{
	//	UPrimitiveComponent* PrimComp = OverlappedComponents[i];
	//	
	//	if (PrimComp && PrimComp->IsSimulatingPhysics() && !PrimComp->GetCollisionShape().IsSphere())
	//	{
	//		const float SphereRadius = OuterSphereComp->GetScaledSphereRadius();
	//		const float ForceStr = -2000.0f;

	//		PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, ForceStr, ERadialImpulseFalloff::RIF_Constant, true);
	//	}
	//}

	count += DeltaTime;
	if (count > lifeTime)
	{
		Destroy();
	}
}

