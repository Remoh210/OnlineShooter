// Fill out your copyright notice in the Description page of Project Settings.


#include "SOC_BPGameState.h"
#include "UnrealNetwork.h"
#include "Engine/World.h"
#include "SOCPlayerController.h"

void ASOC_BPGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{
	//Disable input for Every Pawn
	//for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
	//{
	//	APawn* Pawn = It->Get();
	//	if (Pawn && Pawn->IsLocallyControlled())
	//	{
	//		Pawn->DisableInput(nullptr);
	//	}

	//}

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		ASOCPlayerController* PC = Cast<ASOCPlayerController>(It->Get());
		if (PC && PC->IsLocalController())
		{
			PC->OnMissionCompleted(InstigatorPawn, bMissionSuccess);

			APawn* MyPawn = PC->GetPawn();
			if (MyPawn)
			{
				MyPawn->DisableInput(nullptr);
			}
		}
	}
}
