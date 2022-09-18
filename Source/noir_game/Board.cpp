// Fill out your copyright notice in the Description page of Project Settings.

#include "Board.h"
#include "Public/BoardActor.h"

// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector ABoard::GetBoardLocation(TPair<int, int> board_coords) {
	return { double(board_coords.Key) * 100., double(board_coords.Value) * -100., 0.};
}

void ABoard::AddToBoardMap(ABoardActor* whomst) {
	BoardMap.Add(whomst->GetBoardCoordinates(), whomst);
	if (whomst->canTickTurn()) TickTurnSet.Add(whomst);
}

bool ABoard::TryMove(TPair<int, int> from, TPair<int, int> to) {
	if (!BoardMap.Contains(to)) return true;
	return BoardMap[to]->Action(from);
}

void ABoard::MoveOnBoard(ABoardActor* who, TPair<int, int> to) {
	BoardMap.Remove(who->GetBoardCoordinates());
	who->Move(to);
	AddToBoardMap(who);
}

void ABoard::RemoveFromBoardMap(TPair<int, int> at, ABoardActor* who) {
	if (BoardMap[at] == who)
	{
		BoardMap.Remove(at);
		if (who->canTickTurn())  TickTurnSet.Remove(who);
	}
}

ABoardActor* ABoard::WhoAt(TPair<int, int> at) {
	return BoardMap[at];
}

void ABoard::TickTurnOnBoard() {
	for (auto ticker : TickTurnSet) {
		ticker->TickTurn();
	}
}