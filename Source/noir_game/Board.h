// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Public/IntCoords2D.h"
#include "Board.generated.h"

class ABoardActor;
class ABoardScriptEvent;

UCLASS(Placeable, ShowCategories = (Attributes))
class NOIR_GAME_API ABoard : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)
		int size_x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)
		int size_y;
public:
	// Sets default values for this actor's properties
	ABoard();

	// world transform
	FVector GetBoardLocation(FIntCoords2D);

	// board movement
private:
	bool CanMoveTo(ABoardActor* instigator, FIntCoords2D& to);
	void MoveOnBoard(ABoardActor* who, FIntCoords2D& to);
public:
	UFUNCTION(BlueprintCallable)
	bool MoveActorBy(ABoardActor* who, const FIntCoords2D& by);
	
	// board contents creation and removal
	bool AddToBoard(ABoardActor*);
	void AddEvent(ABoardScriptEvent*);

private:
	typedef TMap < FIntCoords2D, TArray< ABoardActor* > > BoardMapType;
	typedef TMap < ABoardActor*, int > ActorStatesType;

	BoardMapType BoardMap;
	UPROPERTY(VisibleAnywhere, Category = State)
	TMap < ABoardActor*, int > ActorStates;

	TArray < BoardMapType > BoardMapHistory;
	TArray < ActorStatesType > ActorStatesHistory;

	UPROPERTY(VisibleAnywhere, Category = Attributes)
	TArray < ABoardScriptEvent* > BoardEvents;

	void TriggerEvents();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// Time related functions
public:
	UFUNCTION(BlueprintCallable)
	void MakeTurn(ABoardActor* activeBoardActor, const FIntCoords2D& input);
	UFUNCTION(BlueprintCallable)
	void PassTurn();
	UFUNCTION(BlueprintCallable)
	void RewindTurn();
private:
	void TickTurnOnBoard();
	void BackupBoardMap();
};
