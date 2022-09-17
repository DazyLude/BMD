// Fill out your copyright notice in the Description page of Project Settings.


#include "DetectiveActor.h"
#include "..\Source\noir_game\Board.h"

ADetectiveActor::ADetectiveActor() {
	ConstructorHelpers::FObjectFinder<UStaticMesh> VisualMesh(TEXT("/Game/StarterContent/Props/SM_Statue.SM_Statue"));
	SetMesh(VisualMesh);
}

bool ADetectiveActor::Action(TPair<int, int> from) {
	TPair<int, int> to{ 2 * board_x - from.Key, 2 * board_y - from.Value };
	if (MyLittleBoard->TryMove(GetBoardCoordinates(), to)) {
		MyLittleBoard->MoveOnBoard(this, to);
		return true;
	}
	return false;
}