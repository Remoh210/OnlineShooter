// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterOnCppGameMode.generated.h"

UCLASS(minimalapi)
class AShooterOnCppGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShooterOnCppGameMode();

	void CompleteMission(APawn* InstigatorPawn);

	UFUNCTION(BlueprintImplementableEvent, Category = GamePlay)
	void OnMissionCompleted(APawn* InstigatorPawn);
};



