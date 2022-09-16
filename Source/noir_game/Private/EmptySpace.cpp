// Fill out your copyright notice in the Description page of Project Settings.


#include "EmptySpace.h"

AEmptySpace::AEmptySpace() {
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshVisualAsset (TEXT("/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane"));
    if (MeshVisualAsset.Succeeded())
    {
        Mesh->SetStaticMesh(MeshVisualAsset.Object);
        Mesh->SetRelativeLocation(FVector(-0.5f, -0.5f, 0.0f));
        Mesh->SetWorldScale3D(FVector(1.0f));
        Mesh->Activate();
    }
}