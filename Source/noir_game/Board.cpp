// Fill out your copyright notice in the Description page of Project Settings.

#include "Board.h"
#include "Public/BoardActor.h"

// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

void ABoard::AddToBoardMap(ABoardActor* whomst) {
	BoardMap.Add(whomst->GetBoardCoordinates(), whomst);
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
	if (BoardMap[at] == who) BoardMap.Remove(at);
}

ABoardActor* ABoard::WhoAt(TPair<int, int> at) {
	return BoardMap[at];
}