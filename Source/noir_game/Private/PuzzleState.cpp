// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleState.h"

APuzzleState::APuzzleState() {
	cluesHistory = {};
}

bool APuzzleState::LevelComplete() {
	return CollectedClues >= RequiredClues && TimeAvailable >= TimePassed;
}

void APuzzleState::TimeIncrement() {
	++TimePassed;
	cluesHistory.Push(CollectedClues);
}

void APuzzleState::TimeDecrement() {
	--TimePassed;
	CollectedClues = cluesHistory.Pop();
}