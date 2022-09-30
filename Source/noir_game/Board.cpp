// Fill out your copyright notice in the Description page of Project Settings.

#include "Board.h"
#include "Public/PuzzleState.h"
#include "Public/BoardActor.h"
#include "Public/BoardScriptEvent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	size_x = 1;
	size_y = 1;
	BoardEvents = {};
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
}

FVector ABoard::GetBoardLocation(FIntCoords2D board_coords) {
	return { double(board_coords.x) * 100., double(board_coords.y) * -100., 0.};
}

bool ABoard::AddToBoard(ABoardActor* whomst) {
	if (!BoardMap.Contains(whomst->GetBoardCoordinates())) {
		BoardMap.Add(whomst->GetBoardCoordinates(), {});
	}
	BoardMap[whomst->GetBoardCoordinates()].Add(whomst);
	ActorStates.Add( { whomst, whomst->GetState() } );
	return true;
}

void ABoard::AddEvent(ABoardScriptEvent* event) {
	BoardEvents.Add(event);
}

bool ABoard::MoveActorBy(ABoardActor* who, const FIntCoords2D& by) {
	FIntCoords2D to { who->GetBoardCoordinates() + by };
	if (CanMoveTo(who, to)) {
		MoveOnBoard(who, to);
		return true;
	}
	return false;
}

bool ABoard::CanMoveTo(ABoardActor* instigator, FIntCoords2D& to) {
	if (to.x >= size_x || to.y >= size_y) return false;
	if (to.x < -size_x || to.y < -size_x) return false;
	if (!BoardMap.Contains(to)) return true;

	bool canMove{ true }; // can move, unless any actor in the "to" prohibits
	for (auto actorInTargetCell : BoardMap[to]) {
		if (!actorInTargetCell->Action(instigator))
			canMove = false;
	}

	return canMove;
}

void ABoard::MoveOnBoard(ABoardActor* who, FIntCoords2D& to) {
	BoardMap[ who->GetBoardCoordinates() ].Remove(who);
	who->SetBoardCoordinates(to);
	who->MoveInWorld(GetBoardLocation(to));
	AddToBoard(who);
}

void ABoard::MakeTurn(ABoardActor* activeBoardActor, const FIntCoords2D& input) {
	BackupBoardMap();
	MoveActorBy(activeBoardActor, input);
	TickTurnOnBoard();
	TriggerEvents();
}

void ABoard::PassTurn() {
	BackupBoardMap();
	TickTurnOnBoard();
	TriggerEvents();
}

void ABoard::BackupBoardMap() {
	BoardMapHistory.Push(BoardMap);
	ActorStatesHistory.Push(ActorStates);
}

void ABoard::TickTurnOnBoard() {
	for (auto actorStatePair = ActorStates.begin(); actorStatePair != ActorStates.end(); ++actorStatePair) {
		actorStatePair->Key->TickTurn();
		actorStatePair->Value = actorStatePair->Key->GetState();
	}
}

void ABoard::TriggerEvents() {
	for (auto event : BoardEvents) {
		if (event->TriggerCondition()) {
			event->Action();
		}
	}
}

void ABoard::RewindTurn() {
	for (auto cellWithActors : BoardMapHistory.Pop()) {
		for (auto cellActor : cellWithActors.Value) {
			MoveOnBoard(cellActor, cellWithActors.Key);
		}
	}
	ActorStates = ActorStatesHistory.Pop();
	for (auto actorState : ActorStates) {
		actorState.Key->SetState(actorState.Value);
	}
}