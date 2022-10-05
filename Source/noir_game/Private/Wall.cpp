// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"

AWall::AWall() {
    SetTileMesh();
    ConstructorHelpers::FObjectFinder<UMaterialInterface> material (TEXT("/Game/Materials/Wall/WallMat.WallMat"));
    SetMeshMaterial(material);
}