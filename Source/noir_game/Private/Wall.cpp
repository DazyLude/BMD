// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"

AWall::AWall() {
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);
    ConstructorHelpers::FObjectFinder<UStaticMesh> MeshVisualAsset(TEXT("/Game/StarterContent/Props/SM_Rock.SM_Rock"));
    if (MeshVisualAsset.Succeeded())
    {
        Mesh->SetStaticMesh(MeshVisualAsset.Object);
        Mesh->SetRelativeLocation(FVector(-0.5f, -0.5f, 0.0f));
        Mesh->SetWorldScale3D(FVector(1.0f));
        Mesh->Activate();
    }
}

bool AWall::Action(ABoard* Board) {
    return false;
}