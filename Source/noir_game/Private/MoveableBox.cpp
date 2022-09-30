// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveableBox.h"
#include "../Source/noir_game/Board.h"

AMoveableBox::AMoveableBox() {
	ConstructorHelpers::FObjectFinder<UStaticMesh> VisualMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	SetMesh(VisualMesh, 0.7);
}

bool AMoveableBox::Action(ABoardActor* instigator) {
	auto dCoords { GetBoardCoordinates() - instigator->GetBoardCoordinates() };
	if ( MyLittleBoard->MoveActorBy(this, dCoords) ) return true;
	return false;
}