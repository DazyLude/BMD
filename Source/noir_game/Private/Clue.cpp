// Fill out your copyright notice in the Description page of Project Settings.

#include "..\Source\noir_game\Board.h"
#include "Clue.h"

AClue::AClue() {
	ConstructorHelpers::FObjectFinder<UStaticMesh> VisualMesh(TEXT("/Game/StarterContent/Props/SM_Bush.SM_Bush"));
	SetMesh(VisualMesh);
}

bool AClue::Action(TPair<int, int> from) {
	return false;
}