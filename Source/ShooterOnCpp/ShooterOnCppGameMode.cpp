// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ShooterOnCppGameMode.h"
#include "ShooterOnCppHUD.h"
#include "ShooterOnCppCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "SOC_BPGameState.h"

AShooterOnCppGameMode::AShooterOnCppGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AShooterOnCppHUD::StaticClass();

	//Important!!!!!
	GameStateClass = ASOC_BPGameState::StaticClass();
}

void AShooterOnCppGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess)
{
	//InstigatorPawn->DisableInput(nullptr);

	ASOC_BPGameState* GS = GetGameState<ASOC_BPGameState>();
	if (GS)
	{
		GS->MulticastOnMissionComplete(InstigatorPawn, bMissionSuccess);
	}

	OnMissionCompleted(InstigatorPawn, bMissionSuccess);
}
