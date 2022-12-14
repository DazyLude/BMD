// Fill out your copyright notice in the Description page of Project Settings.

#include "Clue.h"
#include "..\Source\noir_game\Board.h"
#include "PuzzleState.h"

AClue::AClue() {
	SetTileMesh();
	ConstructorHelpers::FObjectFinder<UMaterialInterface> material(TEXT("/Game/Materials/Clue/ClueMatGreen.ClueMatGreen"));
	SetMeshMaterial(material);
}

bool AClue::Action(ABoardActor* instigator) {
	if (LifeTime < 0) return true;

	if (instigator->CanCollectClues()) {
		APuzzleState* GS = Cast<APuzzleState>(GetWorld()->GetGameState());
		if (GS != nullptr) {
			GS->CollectedClues += ClueValue;
		}
		SetState(-1);
		return true;
	}

	return false;
}

void AClue::TickTurn() {
	if (isTemporary) --LifeTime;
	if (LifeTime < 0) PseudoDestroy();
}

int AClue::GetState() {
	return LifeTime;
}

void AClue::SetState(int state) {
	LifeTime = state;
	if (LifeTime >= 0) UnPseudoDestroy();
	else PseudoDestroy();
}