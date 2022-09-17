// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoardActor.h"
#include "MoveableBox.generated.h"

/**
 * 
 */
UCLASS()
class NOIR_GAME_API AMoveableBox : public ABoardActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;

	AMoveableBox();
	bool Action(TPair<int, int> from) override;
};
