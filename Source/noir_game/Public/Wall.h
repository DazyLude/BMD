// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoardActor.h"
#include "Wall.generated.h"

/**
 * 
 */
UCLASS()
class NOIR_GAME_API AWall : public ABoardActor
{

	GENERATED_BODY()
public:

	AWall();

protected:
	bool Action(ABoardActor*) override { return false; };

};
