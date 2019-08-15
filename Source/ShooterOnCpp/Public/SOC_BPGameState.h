// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SOC_BPGameState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERONCPP_API ASOC_BPGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	//Sent to all clients if called on server
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnMissionComplete(APawn* InstigatorPawn, bool bMissionSuccess);

	void MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess);

};
