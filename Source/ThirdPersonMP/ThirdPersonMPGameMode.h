// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "ThirdPersonMPGameMode.generated.h"


UCLASS(minimalapi)
class AThirdPersonMPGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	bool MatchStart;

	int MatchRemainTime;

	double countDownRate;

	FTimerHandle MatchTimer;
	
	AThirdPersonMPGameMode();

	void StartMatch();

	void DoCountDown();

	void SetNextCountDown();

	void EndMatch();

	virtual void Tick(float DeltaSeconds) override;
};



