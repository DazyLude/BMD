// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleState.h"

bool APuzzleState::LevelComplete() {
	return CollectedClues >= RequiredClues;
}

void APuzzleState::TimeChanger() {
	TimePassed++;
}