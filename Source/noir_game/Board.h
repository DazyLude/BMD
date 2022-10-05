// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Public/IntCoords2D.h"
#include "Board.generated.h"

class ABoardActor;
class ABoardScriptEvent;
class UCameraComponent;

UCLASS(Placeable)
class NOIR_GAME_API ABoard : public AActor
{
	GENERATED_BODY()
public:
	// singletoneness is guaranteed (or so I think) after component initialization
	UFUNCTION(BlueprintCallable)
	static ABoard* GetBoardInstance();

	// world transform of a cell
	UFUNCTION(BlueprintCallable)
	FVector GetBoardLocation(const FIntCoords2D& where);

	// orthographic camera setup
	UFUNCTION(BlueprintCallable)
	float GetCameraFieldSize();

	// movement on the board
	UFUNCTION(BlueprintCallable)
	bool MoveActorBy(ABoardActor* who, const FIntCoords2D& by);
	UFUNCTION(BlueprintCallable)
	void ForceMoveOnBoard(ABoardActor* who, const FIntCoords2D& to);
	
	// board contents creation
	bool AddToBoard(ABoardActor*);
	void AddEvent(ABoardScriptEvent*);
	
	// Time related functions
	UFUNCTION(BlueprintCallable)
	void MakeTurn(ABoardActor* activeBoardActor, const FIntCoords2D& input);
	UFUNCTION(BlueprintCallable)
	void PassTurn();
	UFUNCTION(BlueprintCallable)
	void RewindTurn();

protected:
	ABoard();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* default_camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int size_x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int size_y;

private:
	static ABoard* _instance;

	typedef TMap < FIntCoords2D, TArray< ABoardActor* > > BoardMapType;
	typedef TMap < ABoardActor*, int > ActorStatesType;

	BoardMapType BoardMap;
	TArray < BoardMapType > BoardMapHistory;

	ActorStatesType ActorStates;
	TArray < ActorStatesType > ActorStatesHistory;

	TArray < ABoardScriptEvent* > BoardEvents;
	TArray < int > ScriptStates;
	TArray < TArray < int >> ScriptStatesHistory;

	virtual void BeginPlay() override;
	virtual void PreInitializeComponents() override;

	bool CanMoveTo(ABoardActor* instigator, const FIntCoords2D& to);
	
	void TickTurnOnBoard();
	void TriggerEvents();
	void BackupBoardMap();
};
