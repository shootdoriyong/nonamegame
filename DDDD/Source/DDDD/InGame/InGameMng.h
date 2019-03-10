// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InGameDefine.h"
#include "InGameMng.generated.h"

/**
 * 
 */

#define BOARD_X	10
#define BOARD_Y 10

class UBoardCtr;
class UObstacleCtr;

UCLASS()
class DDDD_API UInGameMng : public UObject
{
	GENERATED_BODY()
	
public:
	void					Init();
	void					Update(float in_DeltaTime);
	void					Shutdown();
	
	//인게임으로 넘어올 때 호출
	void					Enter();

	//게임 결과 받고 로비로 넘어 갈 때
	void					Exit();

	//실제 게임 시작 시 호출
	void					StartGame();

	UBoardCtr*				GetBoardCtr();
	UObstacleCtr*			GetObstacleCtr();

	void					SetIsMyTurn(bool in_bIsMyTurn);
	bool					GetIsMyTurn();
private:
	UPROPERTY()
	UBoardCtr*				_pBoradCtr;

	UPROPERTY()
	UObstacleCtr*			_pObstacleCtr;

private:
	bool					_bIsMyTurn;
};
