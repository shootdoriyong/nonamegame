// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Board.generated.h"

/**
 * 
 */

class ABoardPieceBase;

UCLASS()
class DDDD_API UBoard : public UObject
{
	GENERATED_BODY()
	
public:
	void					Init();
	void					Update(float in_DeltaTime);
	void					Shutdown();

	void					CreateBoard(bool in_bIsMine, int32 in_X, int32 in_Y);

private:
	//보드 조각 인덱스랑 맵으로 저장하는게 편할수도. 일단 조각에 조각 인덱스 넣을거라 어레이로 쓰자
	UPROPERTY()
	TArray<ABoardPieceBase*> _BoardPiceList;

private:
	bool					_bIsMineBorad;
};
