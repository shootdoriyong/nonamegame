// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InGameMng.generated.h"

/**
 * 
 */

#define BOARD_X	10
#define BOARD_Y 10

class UBoardCtr;

UCLASS()
class DDDD_API UInGameMng : public UObject
{
	GENERATED_BODY()
	
public:
	void					Init();
	void					Update(float in_DeltaTime);
	void					Shutdown();
	
	//�ΰ������� �Ѿ�� �� ȣ��
	void					Enter();

	//���� ��� �ް� �κ�� �Ѿ� �� ��
	void					Exit();

	//���� ���� ���� �� ȣ��
	void					StartGame();

	UBoardCtr*				GetBoardCtr();

private:
	UPROPERTY()
	UBoardCtr*				_pBoradCtr;
};