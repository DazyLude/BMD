// Fill out your copyright notice in the Description page of Project Settings.

#include "../Source/noir_game/Board.h"
#include "MoveableBox.h"

AMoveableBox::AMoveableBox() {
	ConstructorHelpers::FObjectFinder<UStaticMesh> VisualMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	SetMesh(VisualMesh);
}

bool AMoveableBox::Action(TPair<int, int> from) {
	TPair<int, int> to { board_x - from.Key, board_y - from.Value };
	if (MyLittleBoard->TryMove(GetBoardCoordinates(), to)) {
		MyLittleBoard->MoveOnBoard(this, to);
		return true;
	}
	return false;
}