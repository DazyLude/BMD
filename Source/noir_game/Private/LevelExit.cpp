// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelExit.h"
#include "PuzzleState.h"
#include "Kismet/GameplayStatics.h"

ALevelExit::ALevelExit() {
	ConstructorHelpers::FObjectFinder<UStaticMesh> VisualMesh(TEXT("/Game/StarterContent/Props/SM_Chair.SM_Chair"));
	SetMesh(VisualMesh, 1.5);
}

bool ALevelExit::Action(ABoardActor* instigator) {
	if (Cast<APuzzleState>(GetWorld()->GetGameState())->LevelComplete()) {
		UGameplayStatics::OpenLevel(GetWorld(), NextLevel);
		return true;
	}
	return false;
}