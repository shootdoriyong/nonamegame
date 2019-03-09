// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMng.h"
#include "DefineMacro.h"
#include "BoardCtr.h"
#include "ObstacleCtr.h"
#include "DDDDPlayerController.h"

void UInGameMng::Init()
{
	_pBoradCtr = nullptr;
	_pObstacleCtr = nullptr;

	//_bIsMyTurn = false;
	_bIsMyTurn = true; //DEV 항상 나의턴. 추후 게임모드 등을 통해 턴이 바뀌면 바꿔줘야함
}

void UInGameMng::Update(float in_DeltaTime)
{
	if (IS_VALID(_pBoradCtr))
	{
		_pBoradCtr->Update(in_DeltaTime);
	}

	if (IS_VALID(_pObstacleCtr))
	{
		_pObstacleCtr->Update(in_DeltaTime);
	}
}

void UInGameMng::Shutdown()
{
	if (IS_VALID(_pBoradCtr))
	{
		_pBoradCtr->Shutdown();
		_pBoradCtr = nullptr;
	}

	if (IS_VALID(_pObstacleCtr))
	{
		_pObstacleCtr->Shutdown();
		_pObstacleCtr = nullptr;
	}
}

void UInGameMng::Enter()
{
	//시작 전 해줘야 할 것들
	ADDDDPlayerController* pDDDDPC = Cast<ADDDDPlayerController>(GET_MAINFRAMEWORK()->GetGameInstance()->GetWorld()->GetFirstPlayerController());
	if (IS_VALID(pDDDDPC))
	{
		pDDDDPC->PossessToInGamePawn();
	}

	//대기 시간이 있다면 그 이후에
	StartGame();
}

void UInGameMng::StartGame()
{
	_pBoradCtr = NewObject<UBoardCtr>();
	_pBoradCtr->Init();

	//내 보드, 적 보드가 같다고 가정. 혹시 서로 다른 형태의 보드를 쓴다? 그럼 수정 필요
	_pBoradCtr->CreateBoard(BOARD_X, BOARD_Y);

	_pObstacleCtr = NewObject<UObstacleCtr>();
	_pObstacleCtr->Init();

	_pObstacleCtr->SetObstacleList();
}

UBoardCtr* UInGameMng::GetBoardCtr()
{
	return _pBoradCtr;
}

UObstacleCtr* UInGameMng::GetObstacleCtr()
{
	return _pObstacleCtr;
}

void UInGameMng::SetIsMyTurn(bool in_bIsMyTurn)
{
	_bIsMyTurn = in_bIsMyTurn;
}

bool UInGameMng::GetIsMyTurn()
{
	return _bIsMyTurn;
}

void UInGameMng::Exit()
{
	_pBoradCtr = nullptr;
	_pObstacleCtr = nullptr;
}