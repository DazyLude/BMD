// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

ADoor::ADoor() {
	SetTileMesh();
	isClosed = false;
}

void ADoor::Open() {
	isClosed = false;
}

void ADoor::Close() {
	isClosed = true;
}

void ADoor::Switch() {
	isClosed = !isClosed;
}

void ADoor::SetState(int newState) {
	isClosed = newState == 0 ? true : false;
}

int ADoor::GetState() {
	return isClosed ? 0 : 1;
}

bool ADoor::Action(ABoardActor* instigator) {
	return !isClosed;
}