// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

class ABoardActor;

UCLASS(Placeable, ShowCategories = (Attributes))
class NOIR_GAME_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)
		int size_x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)
		int size_y;
	// Sets default values for this actor's properties
	ABoard();

	FVector GetBoardLocation(TPair<int, int>);

	bool TryMove(TPair<int, int>, TPair<int, int>);
	void MoveOnBoard(ABoardActor* who, TPair<int, int>);
	void AddToBoardMap(ABoardActor*);
	void RemoveFromBoardMap(TPair<int, int>, ABoardActor* who);
	ABoardActor* WhoAt(TPair <int, int>);

protected:
	TMap < TPair<int, int>, ABoardActor* > BoardMap;

	TSet<ABoardActor*> TickTurnSet;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void TickTurnOnBoard();
};
