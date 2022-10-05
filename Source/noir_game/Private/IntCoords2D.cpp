// Fill out your copyright notice in the Description page of Project Settings.


#include "IntCoords2D.h"

uint32 GetTypeHash(const FIntCoords2D& hashed) {
	return GetTypeHash(hashed.x) + GetTypeHash(hashed.y);
}


TArray<FIntCoords2D> FIntCoords2D::interpolate(const FIntCoords2D& from, const FIntCoords2D& to) {
	TArray<FIntCoords2D> result{};
	if (to >= from) {
		for (int i_x = from.x; i_x <= to.x; ++i_x) for (int i_y = from.y; i_y <= to.y; ++i_y)
			result.Push({ i_x, i_y });
		return result;
	}
	else return {};
}