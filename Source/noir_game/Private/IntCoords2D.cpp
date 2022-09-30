// Fill out your copyright notice in the Description page of Project Settings.


#include "IntCoords2D.h"

uint32 GetTypeHash(const FIntCoords2D& hashed) {
	return GetTypeHash(hashed.x) + GetTypeHash(hashed.y);
}
