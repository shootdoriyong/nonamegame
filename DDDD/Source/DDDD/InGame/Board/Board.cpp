// Fill out your copyright notice in the Description page of Project Settings.

#include "Board.h"
#include "BoardPieceBase.h"
#include "BoardPieceNormal.h"
#include "DefineMacro.h"

void UBoard::Init()
{
	_BoardPiceList.Empty();

	_bIsMineBorad = false;
}

void UBoard::Update(float in_DeltaTime)
{

}

void UBoard::Shutdown()
{
	for (auto Iter = _BoardPiceList.CreateIterator(); Iter; ++Iter)
	{
		(*Iter)->Destroy();
	}

	_BoardPiceList.Empty();
}

void UBoard::CreateBoard(bool in_bIsMine, int32 in_X, int32 in_Y)
{
	_bIsMineBorad = in_bIsMine;

	int32 BoardIndex = 0;

	for (int32 i = 0; i < in_X; i++)
	{
		for (int32 j = 0; j < in_Y; j++)
		{
			//일단 Normal Board 조각으로만 Board 구성하자
			UClass* pClass = nullptr;
			FString strBPPath = "/Game/Board/BoardNormalPiece.BoardNormalPiece_C";

			pClass = Cast<UClass>(StaticLoadClass(ABoardPieceNormal::StaticClass(), NULL, *strBPPath));

			if (pClass != nullptr)
			{
				//내 보드 , 적 보드 생성위치 세팅. 보드 조각 크기 등등 변수 있어 일단 임의 값 넣고
				FVector Loc = FVector(0, 0, 0);
				FRotator Rot = FRotator(0, 0, 0);

				if (_bIsMineBorad == false)
				{
					Loc += FVector(0, 0, 0);
				}

				FTransform Tr(Rot, Loc, FVector::OneVector);

				ABoardPieceBase* pBoardPiece = Cast<ABoardPieceBase>(GET_MAINFRAMEWORK()->GetGameInstance()->GetWorld()->SpawnActor(pClass, &Tr));
				if (pBoardPiece)
				{
					pBoardPiece->Init(BoardIndex++);
					_BoardPiceList.Add(pBoardPiece);
				}
			}
		}
	}
}
