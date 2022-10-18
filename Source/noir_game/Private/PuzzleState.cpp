// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleState.h"

APuzzleState::APuzzleState() {
	cluesHistory = {};
}

bool APuzzleState::LevelComplete() {
	bool cluesCheck{ RequiredClues == 0 ? true : CollectedClues >= RequiredClues };
	bool timeCheck{ TimeAvailable == 0 ? true : TimeAvailable >= TimePassed };
	return cluesCheck && timeCheck;
}

void APuzzleState::TimeIncrement() {
	++TimePassed;
	cluesHistory.Push(CollectedClues);
}

void APuzzleState::TimeDecrement() {
	--TimePassed;
	CollectedClues = cluesHistory.Pop();
}