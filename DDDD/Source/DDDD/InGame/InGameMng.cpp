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

	//시작 전 해줘야 할 것들

	//대기 시간이 있다면 그 이후에
	StartGame();
}

void UInGameMng::StartGame()
{
	//UE_LOG(LogClass, Warning, TEXT("StartGame in InGameMng Class"));

	_pBoradCtr = NewObject<UBoardCtr>();
	_pBoradCtr->Init();

	//내 보드, 적 보드가 같다고 가정. 혹시 서로 다른 형태의 보드를 쓴다? 그럼 수정 필요
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