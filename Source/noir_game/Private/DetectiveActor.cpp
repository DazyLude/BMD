// Fill out your copyright notice in the Description page of Project Settings.


#include "DetectiveActor.h"
#include "..\Source\noir_game\Board.h"

ADetectiveActor::ADetectiveActor() {
	SetTileMesh();
	ConstructorHelpers::FObjectFinder<UMaterialInterface> material(TEXT("/Game/Materials/Detective/DetectiveMat.DetectiveMat"));
	SetMeshMaterial(material);
}