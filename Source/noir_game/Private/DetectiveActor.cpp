// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Source\noir_game\Board.h"
#include "DetectiveActor.h"

ADetectiveActor::ADetectiveActor() {
	ConstructorHelpers::FObjectFinder<UStaticMesh> VisualMesh(TEXT("/Game/StarterContent/Props/SM_Statue.SM_Statue"));
	SetMesh(VisualMesh);
}

bool ADetectiveActor::Action(TPair<int, int> from) {
	TPair<int, int> to{ board_x - from.Key, board_y - from.Value };
	if (MyLittleBoard->TryMove(GetBoardCoordinates(), to)) {
		MyLittleBoard->MoveOnBoard(this, to);
		return true;
	}
	return false;
}