// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonMPGameMode.h"
#include "ThirdPersonMPTarget.h"
#include "ThirdPersonMPProjectile.h"
#include "ThirdPersonMPCharacter.h"
#include "Engine/World.h"
#include "GameFramework/PlayerState.h"
#include "UObject/ConstructorHelpers.h"


AThirdPersonMPGameMode::AThirdPersonMPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 3.0f;

	MatchStart = false;
}

void AThirdPersonMPGameMode::StartMatch()
{
	if (GEngine)
	{
		FString timeMessage = FString::Printf(TEXT("Game Started."));
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, timeMessage);
		MatchRemainTime = 20;
		countDownRate = 1.0f;
		DoCountDown();
	}
}

void AThirdPersonMPGameMode::DoCountDown() 
{
	
	FString timeMessage = FString::Printf(TEXT("Time remaining: %d."), MatchRemainTime);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, timeMessage);

	MatchRemainTime--;
	if (MatchRemainTime >= 0)
	{
		SetNextCountDown();
	}
	else
	{
		EndMatch();
	}
}

void AThirdPersonMPGameMode::SetNextCountDown() 
{
	
	GetWorldTimerManager().SetTimer(MatchTimer, this, &AThirdPersonMPGameMode::DoCountDown, countDownRate, false);
	
}

void AThirdPersonMPGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (GEngine && MatchStart==false)
	{
		int PlayerCount = 0;
		for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
		{
			PlayerCount++;
		}
		if (PlayerCount > 1) {
			MatchStart = true;
			StartMatch();
		}
	}
}

void AThirdPersonMPGameMode::EndMatch() 
{
	FString endMessage = FString::Printf(TEXT("Game Ended."));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, endMessage);

	FString winnerName = FString::Printf(TEXT("NULL"));
	double winScore = -1.0;

	for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		APlayerState* MyPlayerState = Cast<APlayerState>((*It)->PlayerState);
		FString scoreMessage = FString::Printf(TEXT("%s final score: %.2f."), *(MyPlayerState->GetPlayerName()), MyPlayerState->GetScore());
		if (winScore < MyPlayerState->GetScore()) 
		{
			winnerName = MyPlayerState->GetPlayerName();
			winScore = MyPlayerState->GetScore();
		}
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, scoreMessage);
	}

	FString winMessage = FString::Printf(TEXT("Winner is %s."),*winnerName);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, winMessage);
}

