// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoardActor.h"
#include "LevelExit.generated.h"

/**
 * 
 */
UCLASS()
class NOIR_GAME_API ALevelExit : public ABoardActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, category = Attributes)
		FName NextLevel {"MenuLevel"};

	ALevelExit();
	bool Action(ABoardActor*) override;
};
