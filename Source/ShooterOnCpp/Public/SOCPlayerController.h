// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SOCPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERONCPP_API ASOCPlayerController : public APlayerController
{
	GENERATED_BODY()


	public:

	UFUNCTION(BlueprintImplementableEvent, Category = PlayerController)
	void OnMissionCompleted(APawn* InstigatorPawn, bool bMissionSuccess);

};
