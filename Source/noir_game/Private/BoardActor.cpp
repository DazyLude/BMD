// Fill out your copyright notice in the Description page of Project Settings.

#include "BoardActor.h"
#include "../Source/noir_game/Board.h"
#include "IntCoords2D.h"

// Sets default values
ABoardActor::ABoardActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABoardActor::BeginPlay()
{
	Super::BeginPlay();
    if (MyLittleBoard != nullptr && MyLittleBoard->AddToBoard(this))
        SetActorLocation(MyLittleBoard->GetBoardLocation(boardCoords));
    else BeginDestroy();
}

FIntCoords2D ABoardActor::GetBoardCoordinates() {
	return boardCoords;
}

void ABoardActor::SetBoardCoordinates(FIntCoords2D new_coords) {
    boardCoords = new_coords;
}

void ABoardActor::MoveInWorld(FVector where) {
    SetActorLocation(where);
}

void ABoardActor::SetMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>& MeshVisualAsset, double scale_mod = 1.0) {
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);
    if (MeshVisualAsset.Succeeded())
    {
        Mesh->SetStaticMesh(MeshVisualAsset.Object);
        Mesh->SetRelativeLocation(FVector(-0.5f, -0.5f, 0.0f));
        Mesh->SetWorldScale3D(FVector(scale_mod));
        Mesh->Activate();
    }
}

void ABoardActor::PseudoDestroy() {
    if (!isPseudoDestroyed) {
        isPseudoDestroyed = true;
        Mesh->SetHiddenInGame(true);
    }
}

void ABoardActor::UnPseudoDestroy() {
    if (isPseudoDestroyed) {
        isPseudoDestroyed = false;
        Mesh->SetHiddenInGame(false);
    }
}
