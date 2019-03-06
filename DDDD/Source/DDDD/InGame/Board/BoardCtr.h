// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BoardCtr.generated.h"

/**
 * 
 */
class UBoard;

UCLASS()
class DDDD_API UBoardCtr : public UObject
{
	GENERATED_BODY()
	
public:
	void					Init();
	void					Update(float in_DeltaTime);
	void					Shutdown();

	UBoard*					GetMyBoard();
	UBoard*					GetEnemyBoard();

	void					CreateBoard(int32 in_X, int32 in_Y);
private:
	UPROPERTY()
	UBoard*					_pMyBoard;

	UPROPERTY()
	UBoard*					_pEnemyBoard;
};
