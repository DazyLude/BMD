// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"

AWall::AWall() {
    ConstructorHelpers::FObjectFinder<UStaticMesh> VisualMesh(TEXT("/Game/StarterContent/Props/SM_Rock.SM_Rock"));
    SetMesh(VisualMesh, 0.5);
}