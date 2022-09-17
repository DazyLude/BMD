// Fill out your copyright notice in the Description page of Project Settings.

#include "../Source/noir_game/Board.h"
#include "BoardActor.h"

// Sets default values
ABoardActor::ABoardActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoardActor::BeginPlay()
{
	Super::BeginPlay();
	MyLittleBoard->AddToBoardMap(this);
}

// Called every frame
void ABoardActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TPair<int, int> ABoardActor::GetBoardCoordinates() {
	return { board_x, board_y };
}
