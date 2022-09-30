// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IntCoords2D.h"
#include "BoardActor.generated.h"

class ABoard;

UCLASS(Abstract)
class NOIR_GAME_API ABoardActor : public AActor
{
	GENERATED_BODY()
	
public:
	ABoardActor();
	virtual ~ABoardActor() {};

	// board functionality
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)
	ABoard* MyLittleBoard {};

	virtual bool Action(ABoardActor* instigator) { return true; };
	virtual bool CanCollectClues() { return false; };

	// board coordinates and their manipulation
protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)
	FIntCoords2D boardCoords;

public:
	FIntCoords2D GetBoardCoordinates();
	void SetBoardCoordinates(FIntCoords2D new_xy);
	virtual void MoveInWorld(FVector where);

protected:
	// Sets mesh in children class constructors
	void SetMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>&, double);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// methods to hide object if it is expired
private:
	bool isPseudoDestroyed{ false };
protected:
	void PseudoDestroy();
	void UnPseudoDestroy();

	// turn ticking
public:
	virtual void TickTurn() {};
	virtual int GetState() { return 0; };
	virtual void SetState(int state) {};
};
