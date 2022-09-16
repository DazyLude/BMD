// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardActor.generated.h"

class ABoard;

UCLASS()
class NOIR_GAME_API ABoardActor : public AActor
{
	GENERATED_BODY()
	
public:	
	bool interactable;
	bool Action(ABoard* Board);
	// Sets default values for this actor's properties
	ABoardActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
