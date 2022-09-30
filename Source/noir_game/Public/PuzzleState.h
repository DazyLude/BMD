// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PuzzleState.generated.h"


class ABoardActor;

/**
 * 
 */
UCLASS()
class NOIR_GAME_API APuzzleState : public AGameStateBase
{
	
public:
	GENERATED_BODY()

	APuzzleState();
	UPROPERTY(BlueprintReadWrite, Category = ImportantActors)
	ABoardActor* PlayerControlledBoardActor;
	UPROPERTY(BlueprintReadWrite, Category = PuzzleProgress)
	int TimeAvailable;
	UPROPERTY(BlueprintReadWrite, Category = PuzzleProgress)
	int TimePassed;
	UPROPERTY(BlueprintReadWrite, Category = PuzzleProgress)
	int RequiredClues;
	UPROPERTY(BlueprintReadWrite, Category = PuzzleProgress)
	int CollectedClues;
	UFUNCTION(BlueprintCallable)
	bool LevelComplete();
	UFUNCTION(BlueprintCallable)
	void TimeIncrement();
	UFUNCTION(BlueprintCallable)
	void TimeDecrement();

private:
	TArray<int> cluesHistory;
};
