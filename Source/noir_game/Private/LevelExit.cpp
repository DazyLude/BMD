// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelExit.h"
#include "PuzzleState.h"
#include "Kismet/GameplayStatics.h"

ALevelExit::ALevelExit() {
	SetTileMesh();
	ConstructorHelpers::FObjectFinder<UMaterialInterface> material(TEXT("/Game/Materials/Exit/ExitMatRed.ExitMatRed"));
	SetMeshMaterial(material);
}

bool ALevelExit::Action(ABoardActor* instigator) {
	if (Cast<APuzzleState>(GetWorld()->GetGameState())->LevelComplete()) {
		UGameplayStatics::OpenLevel(GetWorld(), NextLevel);
		return true;
	}
	return false;
}