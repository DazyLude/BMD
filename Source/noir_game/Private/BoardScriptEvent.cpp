// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardScriptEvent.h"
#include "../Source/noir_game/Board.h"

void ABoardScriptEvent::Action_Implementation() {};

bool ABoardScriptEvent::TriggerCondition_Implementation() { return false; };

// Sets default values
ABoardScriptEvent::ABoardScriptEvent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoardScriptEvent::BeginPlay()
{
	Super::BeginPlay();
	board->AddEvent(this);
}

// Called every frame
void ABoardScriptEvent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

