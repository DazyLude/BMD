// Fill out your copyright notice in the Description page of Project Settings.


#include "DetectiveActor.h"
#include "..\Source\noir_game\Board.h"

ADetectiveActor::ADetectiveActor() {
	ConstructorHelpers::FObjectFinder<UStaticMesh> VisualMesh(TEXT("/Game/StarterContent/Props/SM_Statue.SM_Statue"));
	SetMesh(VisualMesh, 1.5);
}