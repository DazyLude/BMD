// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoardActor.h"
#include "EmptySpace.generated.h"

/**
 * 
 */
UCLASS()
class NOIR_GAME_API AEmptySpace : public ABoardActor
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;

	AEmptySpace();

protected:
	bool interactable {false};
};
