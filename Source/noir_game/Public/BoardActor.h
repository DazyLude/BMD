// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardActor.generated.h"

class ABoard;

UCLASS(Abstract)
class NOIR_GAME_API ABoardActor : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = Attributes)
		ABoard* MyLittleBoard;

	virtual bool Action(TPair<int, int> from) { return true; };
	// Sets default values for this actor's properties
	ABoardActor();
	TPair<int, int> GetBoardCoordinates();
	void Move(TPair<int, int>);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)
		int board_x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)
		int board_y;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
