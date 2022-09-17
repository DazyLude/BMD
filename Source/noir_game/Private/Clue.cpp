// Fill out your copyright notice in the Description page of Project Settings.

#include "Clue.h"
#include "..\Source\noir_game\Board.h"
#include "PuzzleState.h"

AClue::AClue() {
	ConstructorHelpers::FObjectFinder<UStaticMesh> VisualMesh(TEXT("/Game/StarterContent/Props/SM_Bush.SM_Bush"));
	SetMesh(VisualMesh, 1.);
}

bool AClue::Action(TPair<int, int> from) {
	if (MyLittleBoard->WhoAt(from)->CanCollectClues) {
		APuzzleState* GS = Cast<APuzzleState>(GetWorld()->GetGameState());
		if (GS != nullptr) {
			GS->CollectedClues += ClueValue;
		}
		MyLittleBoard->RemoveFromBoardMap(GetBoardCoordinates(), this);
		Mesh->SetHiddenInGame(true);
		return true;
	}
	return false;
}

void AClue::LifeTimeChanger() {
	if (LifeTime > 0) {
		LifeTime--;
	}
}