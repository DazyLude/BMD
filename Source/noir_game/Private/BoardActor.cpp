// Fill out your copyright notice in the Description page of Project Settings.

#include "BoardActor.h"
#include "../Source/noir_game/Board.h"

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
    if (MyLittleBoard != nullptr) {
	    MyLittleBoard->AddToBoardMap(this);
        Move(GetBoardCoordinates());
    }
    else BeginDestroy();
}


// Called every frame
void ABoardActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TPair<int, int> ABoardActor::GetBoardCoordinates() {
	return { board_x, board_y };
}

void ABoardActor::Move(TPair<int, int> to) {
	board_x = to.Key;
	board_y = to.Value;
    SetActorLocation(MyLittleBoard->GetBoardLocation({ board_x, board_y }));
}

void ABoardActor::MoveBy(int dx, int dy) {
    TPair<int, int> to{ board_x + dx, board_y + dy };
    if (MyLittleBoard->TryMove(GetBoardCoordinates(), to))
        MyLittleBoard->MoveOnBoard(this, to);
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
    MyLittleBoard->RemoveFromBoardMap(GetBoardCoordinates(), this);
    Mesh->SetHiddenInGame(true);
}
