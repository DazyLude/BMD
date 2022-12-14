// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoardActor.h"
#include "DetectiveActor.generated.h"

/**
 * 
 */
UCLASS()
class NOIR_GAME_API ADetectiveActor : public ABoardActor
{
	GENERATED_BODY()
public:
	ADetectiveActor();
	bool Action(ABoardActor*) override { return false; };
	bool CanCollectClues() override { return true; };
};
