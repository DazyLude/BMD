// Fill out your copyright notice in the Description page of Project Settings.


#include "EmptySpace.h"

AEmptySpace::AEmptySpace() {
	ConstructorHelpers::FObjectFinder<UStaticMesh> VisualMesh (TEXT("/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane"));
	SetMesh(VisualMesh);
}