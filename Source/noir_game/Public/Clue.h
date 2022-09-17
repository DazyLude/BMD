// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoardActor.h"
#include "Clue.generated.h"

/**
 * 
 */
UCLASS()
class NOIR_GAME_API AClue : public ABoardActor
{
	GENERATED_BODY()
public:
	AClue();
	bool Action(TPair<int, int>) override;
	UPROPERTY(EditAnywhere, category = Attributes)
	int ClueValue {0};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = Attributes)
		int LifeTime;
	UFUNCTION(BlueprintCallable)
		void LifeTimeChanger();
};
