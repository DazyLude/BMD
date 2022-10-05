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

	// gameplay behavior
	virtual bool Action(ABoardActor* instigator) { return true; };
	virtual void TickTurn() {};

	virtual int GetState() { return 0; };
	virtual void SetState(int state) {};

	virtual bool CanCollectClues() { return false; };

	// board coordinates and their manipulation
	FIntCoords2D GetBoardCoordinates();
	void SetBoardCoordinates(FIntCoords2D new_xy);
	virtual void MoveInWorld(FVector where);

protected:
	ABoard* MyLittleBoard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)
	FIntCoords2D boardCoords;

	// Sets mesh in children class's constructors
	void SetTileMesh();
	void SetMeshMaterial(ConstructorHelpers::FObjectFinder<UMaterialInterface>& mat);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// methods to hide and show object on board without destroying it
	void PseudoDestroy();
	void UnPseudoDestroy();

private:
	void SetMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>&, double);
	bool isPseudoDestroyed{ false };
};
