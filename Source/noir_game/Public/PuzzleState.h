// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PuzzleState.generated.h"

/**
 * 
 */
UCLASS()
class NOIR_GAME_API APuzzleState : public AGameStateBase
{
public:
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, Category = PuzzleProgress)
	int RequiredClues;
	UPROPERTY(BlueprintReadWrite, Category = PuzzleProgress)
	int CollectedClues;
	UFUNCTION(BlueprintCallable)
	bool LevelComplete();
};