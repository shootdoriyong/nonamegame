// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InGameDefine.h"
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
	bool					IsMineBoard();

	bool					GetBoardPieceState(int32 in_BardPieceIndex, EBOARD_PIECE_STATE_TYPE& out_eBoardPieceState);
	bool					SetBoardPieceState(int32 in_BardPieceIndex, EBOARD_PIECE_STATE_TYPE in_eBoardPieceState);
private:
	UPROPERTY()
	TMap<int32, ABoardPieceBase*> _BoardPieceMap;

private:
	bool					_bIsMineBorad;
};
