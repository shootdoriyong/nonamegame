// Fill out your copyright notice in the Description page of Project Settings.

#include "BoardCtr.h"
#include "Board.h"
#include "DefineMacro.h"

void UBoardCtr::Init()
{
	_pMyBoard = nullptr;
	_pEnemyBoard = nullptr;
}

void UBoardCtr::Update(float in_DeltaTime)
{
	if (IS_VALID(_pMyBoard))
		_pMyBoard->Update(in_DeltaTime);

	if (IS_VALID(_pEnemyBoard))
		_pEnemyBoard->Update(in_DeltaTime);
}

void UBoardCtr::Shutdown()
{
	if (IS_VALID(_pMyBoard))
	{
		_pMyBoard->Shutdown();
		_pMyBoard = nullptr;
	}
	
	if (IS_VALID(_pEnemyBoard))
	{
		_pEnemyBoard->Shutdown();
		_pEnemyBoard = nullptr;
	}
}

UBoard*	UBoardCtr::GetMyBoard()
{
	return _pMyBoard;
}

UBoard* UBoardCtr::GetEnemyBoard()
{
	return _pEnemyBoard;
}

void UBoardCtr::CreateBoard(int32 in_X, int32 in_Y)
{
	_pMyBoard = NewObject<UBoard>();
	_pMyBoard->Init();
	_pMyBoard->CreateBoard(true, in_X, in_Y);

	_pEnemyBoard = NewObject<UBoard>();
	_pEnemyBoard->Init();
	_pEnemyBoard->CreateBoard(false, in_X, in_Y);
}

