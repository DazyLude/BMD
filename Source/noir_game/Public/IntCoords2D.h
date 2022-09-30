// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IntCoords2D.generated.h"

USTRUCT(BlueprintType)
struct FIntCoords2D
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int y;

	FIntCoords2D(int in_x, int in_y) : x(in_x), y(in_y) {};
	FIntCoords2D() : FIntCoords2D(0, 0) {};
	FIntCoords2D(const FIntCoords2D& other) : FIntCoords2D(other.x, other.y) {};
	~FIntCoords2D() {};

	FIntCoords2D& operator=(const FIntCoords2D& rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
		return *this;
	}

	FIntCoords2D operator+(const FIntCoords2D& rhs) const {
		return FIntCoords2D(x + rhs.x, y + rhs.y);
	}

	FIntCoords2D operator-(const FIntCoords2D& rhs) const {
		return FIntCoords2D(x - rhs.x, y - rhs.y);
	}

	bool operator==(const FIntCoords2D& rhs) const {
		return x == rhs.x && y == rhs.y;
	}

	friend uint32 GetTypeHash(const FIntCoords2D& hashed);
};