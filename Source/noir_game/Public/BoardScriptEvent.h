// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardScriptEvent.generated.h"

class ABoard;
class ABoardActor;

UCLASS()
class NOIR_GAME_API ABoardScriptEvent : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)
	TArray < ABoardActor* > importantActors;

	UFUNCTION(BlueprintNativeEvent)
	bool TriggerCondition();

	UFUNCTION(BlueprintNativeEvent)
	void Action();

	UFUNCTION(BlueprintNativeEvent)
	int GetState();

	UFUNCTION(BlueprintNativeEvent)
	void SetState(int state);

	// Sets default values for this actor's properties
	ABoardScriptEvent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category = Attributes)
	ABoard* board;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
