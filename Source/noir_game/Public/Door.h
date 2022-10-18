// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoardActor.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class NOIR_GAME_API ADoor : public ABoardActor
{
	GENERATED_BODY()
public:
	ADoor();
	UFUNCTION(BlueprintCallable)
	void Open();
	UFUNCTION(BlueprintCallable)
	void Close();
	UFUNCTION(BlueprintCallable)
	void Switch();

	void SetState(int newState) override;
	int GetState() override;
	bool Action(ABoardActor* instigator) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Attributes")
	bool isClosed;
};
