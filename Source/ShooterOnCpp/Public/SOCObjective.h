// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SOCObjective.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EAmmoType : uint8
{
	AE_Fire 	UMETA(DisplayName = "FireAmmo"),
	AE_Bolt 	UMETA(DisplayName = "BoltAmmo"),
	AE_else		UMETA(DisplayName = "TBD")
};

UCLASS()
class SHOOTERONCPP_API ASOCObjective : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASOCObjective();

protected:
	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	class UParticleSystem* PickupFx;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EAmmoType AmmoType;


	virtual void BeginPlay() override;

	void PlayEffects();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
