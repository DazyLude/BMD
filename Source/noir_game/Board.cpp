// Fill out your copyright notice in the Description page of Project Settings.

#include "Board.h"
#include "Public/PuzzleState.h"
#include "Public/BoardActor.h"
#include "Public/BoardScriptEvent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

const float CELL_SIZE_IN_ENGINE_UNITS{ 100. };

// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	size_x = 1;
	size_y = 1;
	BoardEvents = {};

	default_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("default camera"));
	default_camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	default_camera->SetOrthoNearClipPlane(0.);
	default_camera->SetOrthoFarClipPlane(150.);
	default_camera->PostProcessSettings.MotionBlurAmount = 0;
	default_camera->PostProcessSettings.bOverride_AutoExposureMaxBrightness = true;
	default_camera->PostProcessSettings.AutoExposureMaxBrightness = 0.15;
	default_camera->PostProcessSettings.bOverride_AutoExposureMinBrightness = true;
	default_camera->PostProcessSettings.AutoExposureMinBrightness = 0.15;
	default_camera->Activate();
}

ABoard* ABoard::_instance = nullptr;

ABoard* ABoard::GetBoardInstance() {
	if (_instance == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Tried accessing board instance before component initialization is complete. Don't do that!"));
	}
	return _instance;
}

void ABoard::PreInitializeComponents() {
	_instance = this;
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
	FVector point_down{ 0., 0., -1. };
	default_camera->SetWorldRotation(point_down.Rotation());
	default_camera->AddLocalRotation({ 0., 0., -90. });
	default_camera->SetWorldLocation({ 0., 0., 100. });
	default_camera->OrthoWidth = GetCameraFieldSize();
	GetWorld()->GetFirstPlayerController()->SetViewTarget(this);
}

FVector ABoard::GetBoardLocation(const FIntCoords2D& board_coords) {
	return { double(board_coords.x) * CELL_SIZE_IN_ENGINE_UNITS, double(board_coords.y) * CELL_SIZE_IN_ENGINE_UNITS * -1., 0.};
}

float ABoard::GetCameraFieldSize() {
	return CELL_SIZE_IN_ENGINE_UNITS * float(size_x >= size_y ? (size_x + 1) * 2 : (size_y + 1) * 2) * default_camera->AspectRatio;
}

bool ABoard::AddToBoard(ABoardActor* whomst) {
	if (!BoardMap.Contains(whomst->GetBoardCoordinates())) {
		BoardMap.Add(whomst->GetBoardCoordinates(), {});
	}
	BoardMap[whomst->GetBoardCoordinates()].Add(whomst);
	ActorStates.Add( { whomst, whomst->GetState() } );
	return true;
}

void ABoard::AddEvent(ABoardScriptEvent* event) {
	BoardEvents.Add(event);
	ScriptStates.Add(event->GetState());

}

bool ABoard::MoveActorBy(ABoardActor* who, const FIntCoords2D& by) {
	FIntCoords2D to { who->GetBoardCoordinates() + by };
	if (CanMoveTo(who, to)) {
		ForceMoveOnBoard(who, to);
		return true;
	}
	return false;
}

bool ABoard::CanMoveTo(ABoardActor* instigator, const FIntCoords2D& to) {
	if (to.x >= size_x || to.y >= size_y) return false;
	if (to.x < -size_x || to.y < -size_x) return false;
	if (!BoardMap.Contains(to)) return true;

	bool canMove{ true }; // can move, unless any actor in the "to" prohibits
	for (auto actorInTargetCell : BoardMap[to]) {
		if (!actorInTargetCell->Action(instigator))
			canMove = false;
	}

	return canMove;
}

void ABoard::ForceMoveOnBoard(ABoardActor* who, const FIntCoords2D& to) {
	BoardMap[ who->GetBoardCoordinates() ].Remove(who);
	who->SetBoardCoordinates(to);
	who->MoveInWorld(GetBoardLocation(to));
	AddToBoard(who);
}

void ABoard::MakeTurn(ABoardActor* activeBoardActor, const FIntCoords2D& input) {
	BackupBoardMap();
	MoveActorBy(activeBoardActor, input);
	TickTurnOnBoard();
	TriggerEvents();
}

void ABoard::PassTurn() {
	BackupBoardMap();
	TickTurnOnBoard();
	TriggerEvents();
}

void ABoard::BackupBoardMap() {
	BoardMapHistory.Push(BoardMap);
	ActorStatesHistory.Push(ActorStates);
	ScriptStatesHistory.Push(ScriptStates);
}

void ABoard::TickTurnOnBoard() {
	for (auto actorStatePair = ActorStates.begin(); actorStatePair != ActorStates.end(); ++actorStatePair) {
		actorStatePair->Key->TickTurn();
		actorStatePair->Value = actorStatePair->Key->GetState();
	}
}

void ABoard::TriggerEvents() {
	for (auto scriptActorIndex = 0; scriptActorIndex < BoardEvents.Num(); ++scriptActorIndex) {
		auto script = BoardEvents[scriptActorIndex];
		if (script->TriggerCondition())
			script->Action();
		ScriptStates[scriptActorIndex] = script->GetState();
	}
}

void ABoard::RewindTurn() {
	for (auto cellWithActors : BoardMapHistory.Pop()) {
		for (auto cellActor : cellWithActors.Value) {
			ForceMoveOnBoard(cellActor, cellWithActors.Key);
		}
	}
	ActorStates = ActorStatesHistory.Pop();
	for (auto actorState : ActorStates) {
		actorState.Key->SetState(actorState.Value);
	}
	ScriptStates = ScriptStatesHistory.Pop();
	for (auto scriptActorIndex = 0; scriptActorIndex < BoardEvents.Num(); ++scriptActorIndex) {
		BoardEvents[scriptActorIndex]->SetState(ScriptStates[scriptActorIndex]);
	}
	TriggerEvents();
}