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
	_bIsMyTurn = true; //DEV �׻� ������. ���� ���Ӹ�� ���� ���� ���� �ٲ�� �ٲ������
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
	//���� �� ����� �� �͵�
	ADDDDPlayerController* pDDDDPC = Cast<ADDDDPlayerController>(GET_MAINFRAMEWORK()->GetGameInstance()->GetWorld()->GetFirstPlayerController());
	if (IS_VALID(pDDDDPC))
	{
		pDDDDPC->PossessToInGamePawn();
	}

	//��� �ð��� �ִٸ� �� ���Ŀ�
	StartGame();
}

void UInGameMng::StartGame()
{
	_pBoradCtr = NewObject<UBoardCtr>();
	_pBoradCtr->Init();

	//�� ����, �� ���尡 ���ٰ� ����. Ȥ�� ���� �ٸ� ������ ���带 ����? �׷� ���� �ʿ�
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