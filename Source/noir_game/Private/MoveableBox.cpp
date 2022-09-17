// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveableBox.h"
#include "../Source/noir_game/Board.h"

AMoveableBox::AMoveableBox() {
	ConstructorHelpers::FObjectFinder<UStaticMesh> VisualMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	SetMesh(VisualMesh, 0.7);
}

bool AMoveableBox::Action(TPair<int, int> from) {
	TPair<int, int> to { 2 * board_x - from.Key, 2 * board_y - from.Value };
	if (MyLittleBoard->TryMove(GetBoardCoordinates(), to)) {
		MyLittleBoard->MoveOnBoard(this, to);
		return true;
	}
	return false;
}