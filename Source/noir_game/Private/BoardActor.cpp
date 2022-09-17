// Fill out your copyright notice in the Description page of Project Settings.

#include "../Source/noir_game/Board.h"
#include "BoardActor.h"

// Sets default values
ABoardActor::ABoardActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoardActor::BeginPlay()
{
	Super::BeginPlay();
	MyLittleBoard->AddToBoardMap(this);
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
    auto dx = to.Key - board_x;
    auto dy = to.Value - board_y;
	board_x = to.Key;
	board_y = to.Value;
    auto start_location = GetActorLocation();
    SetActorLocation({ start_location[0] + double(dx), start_location[1] + double(dy), start_location[2] });
}

void ABoardActor::SetMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>& MeshVisualAsset) {
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);
    if (MeshVisualAsset.Succeeded())
    {
        Mesh->SetStaticMesh(MeshVisualAsset.Object);
        Mesh->SetRelativeLocation(FVector(-0.5f, -0.5f, 0.0f));
        Mesh->SetWorldScale3D(FVector(1.0f));
        Mesh->Activate();
    }
}
