// Fill out your copyright notice in the Description page of Project Settings.

#include "BoardActor.h"
#include "../Source/noir_game/Board.h"
#include "IntCoords2D.h"

const float MOVE_TIME_LENGTH{ 0.1 };

// Sets default values
ABoardActor::ABoardActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABoardActor::OnConstruction(const FTransform& Transform) {
    Super::OnConstruction(Transform);
    auto BoardInstance = ABoard::GetBoardInstance();
    if (!BoardInstance) return;

    if (FIntCoords2D(0, 0) == boardCoords) {
        boardCoords = BoardInstance->RoundToBoardCoords(Transform.GetLocation());
        SetActorLocation(BoardInstance->GetBoardLocation(boardCoords));
    }
    else {
        auto tempLocation = BoardInstance->GetBoardLocation(boardCoords);
        SetActorLocation({ tempLocation[0], tempLocation[1], Transform.GetLocation()[2] });
    }
}

// Called when the game starts or when spawned
void ABoardActor::BeginPlay()
{
    Super::BeginPlay();
    MyLittleBoard = ABoard::GetBoardInstance();
    if (MyLittleBoard != nullptr && MyLittleBoard->AddToBoard(this))
        SetActorLocation(MyLittleBoard->GetBoardLocation(boardCoords));
}

FIntCoords2D ABoardActor::GetBoardCoordinates() {
	return boardCoords;
}

void ABoardActor::SetBoardCoordinates(FIntCoords2D new_coords) {
    boardCoords = new_coords;
}

void ABoardActor::MoveInWorld(const FVector& where) {
    moveBuffer.Empty();
    moveBuffer.Push({ MOVE_TIME_LENGTH, SubstituteZ(where) });
    moveBuffer.Push({ 0., GetActorLocation() });
    timeMoving = 0.;
    isMoving = true;
}

void ABoardActor::Tick(float deltaTime) {
    if (isMoving) {
        timeMoving += deltaTime;
        MoveABit();
    }

}

void ABoardActor::MoveABit() {
    if (moveBuffer[moveBuffer.Num() - 2].Key < timeMoving) {
        // if we're gone beyond previous "to" point - we go to the next interval
        moveBuffer.Pop();
    }

    if (moveBuffer.Num() < 2) {
        // if that's left us with buffer with only one point - we've reached the end
        SetActorLocation(moveBuffer.Pop().Value);
        isMoving = false;
        return;
    }

    // we're interpolating between two movepoints based on how much time has passed since the beginning of the movement
    TimestampedLocation& from{ moveBuffer.Last() };
    TimestampedLocation& to{ moveBuffer[moveBuffer.Num() - 2] };
    SetActorLocation(LerpLocations(from, to));
}

FVector ABoardActor::LerpLocations(const TimestampedLocation& from, const TimestampedLocation& to) {
    return from.Value + (to.Value - from.Value) * (timeMoving - from.Key) / (to.Key - from.Key);
}

FVector ABoardActor::SubstituteZ(const FVector& where) {
    return { where[0], where[1], this->GetActorLocation()[2] };
}

void ABoardActor::SetMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>& MeshVisualAsset, double scale_mod) {
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);
    if (MeshVisualAsset.Succeeded())
    {
        Mesh->SetStaticMesh(MeshVisualAsset.Object);
        Mesh->SetRelativeLocation(FVector(-0.5f, -0.5f, 0.0f));
        Mesh->SetWorldScale3D(FVector(scale_mod));
        Mesh->Activate();
        SetRootComponent(Mesh);
    }
}

void ABoardActor::SetTileMesh() {
    ConstructorHelpers::FObjectFinder<UStaticMesh> VisualMesh(TEXT("/Game/Materials/FlatMesh.FlatMesh"));
    SetMesh(VisualMesh, 1);
}

void ABoardActor::SetMeshMaterial(ConstructorHelpers::FObjectFinder<UMaterialInterface>& mat) {
    if (Mesh == nullptr) return;
    if (mat.Succeeded()) {
        Mesh->SetMaterial(0, mat.Object);
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
