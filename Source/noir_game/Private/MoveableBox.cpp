// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveableBox.h"
#include "../Source/noir_game/Board.h"

AMoveableBox::AMoveableBox() {
	SetTileMesh();
	ConstructorHelpers::FObjectFinder<UMaterialInterface> material(TEXT("/Game/Materials/Box/BoxMat.BoxMat"));
	SetMeshMaterial(material);
}

bool AMoveableBox::Action(ABoardActor* instigator) {
	if (instigator->CanCollectClues()) {
		auto dCoords{ GetBoardCoordinates() - instigator->GetBoardCoordinates() };
		if (MyLittleBoard->MoveActorBy(this, dCoords)) return true;
	}
	return false;
}