// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMng.h"
#include "BoardCtr.h"
#include "DefineMacro.h"

void UInGameMng::Init()
{
	_pBoradCtr = nullptr;
}

void UInGameMng::Update(float in_DeltaTime)
{
	if (IS_VALID(_pBoradCtr))
	{
		_pBoradCtr->Update(in_DeltaTime);
	}
}

void UInGameMng::Shutdown()
{
	if (IS_VALID(_pBoradCtr))
	{
		_pBoradCtr->Shutdown();
		_pBoradCtr = nullptr;
	}
}

void UInGameMng::Enter()
{
	//UE_LOG(LogClass, Warning, TEXT("Enter in InGameMng Class"));

	//���� �� ����� �� �͵�

	//��� �ð��� �ִٸ� �� ���Ŀ�
	StartGame();
}

void UInGameMng::StartGame()
{
	//UE_LOG(LogClass, Warning, TEXT("StartGame in InGameMng Class"));

	_pBoradCtr = NewObject<UBoardCtr>();
	_pBoradCtr->Init();

	//�� ����, �� ���尡 ���ٰ� ����. Ȥ�� ���� �ٸ� ������ ���带 ����? �׷� ���� �ʿ�
	_pBoradCtr->CreateBoard(BOARD_X, BOARD_Y);
}

UBoardCtr* UInGameMng::GetBoardCtr()
{
	return _pBoradCtr;
}

void UInGameMng::Exit()
{
	_pBoradCtr = nullptr;
}