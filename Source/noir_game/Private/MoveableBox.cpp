// Fill out your copyright notice in the Description page of Project Settings.

#include "../Source/noir_game/Board.h"
#include "MoveableBox.h"

AMoveableBox::AMoveableBox() {
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);
    ConstructorHelpers::FObjectFinder<UStaticMesh> MeshVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
    if (MeshVisualAsset.Succeeded())
    {
        Mesh->SetStaticMesh(MeshVisualAsset.Object);
        Mesh->SetRelativeLocation(FVector(-0.5f, -0.5f, 0.0f));
        Mesh->SetWorldScale3D(FVector(1.0f));
        Mesh->Activate();
    }
}

bool AMoveableBox::Action(TPair<int, int> from) {
	TPair<int, int> to { board_x - from.Key, board_y - from.Key };
	if (MyLittleBoard->TryMove(GetBoardCoordinates(), to))
		MyLittleBoard->MoveOnBoard(this, to);
	return false;
}