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

	for (int32 i = 0; i < in_Y; i++)
	{
		for (int32 j = 0; j < in_X; j++)
		{
			//일단 Normal Board 조각으로만 Board 구성하자
			UClass* pClass = nullptr;
			FString strBPPath = "/Game/Board/BoardNormalPiece.BoardNormalPiece_C";

			pClass = Cast<UClass>(StaticLoadClass(ABoardPieceNormal::StaticClass(), NULL, *strBPPath));

			if (pClass != nullptr)
			{
				//내 보드 , 적 보드 생성위치 세팅. 보드 조각 크기 등등 변수 있어 일단 임의 값 넣고

				///내 보드 좌하단 부터 시작. 0, 0, 0을 중점으로. 생성(인덱스) 순서 = 좌하단 -> 우상단 순으로
				//19.03.08 위 내용 수정함 좌상단 부터 우 하단 순으로 생성되도록. 왜? 장애물 생성시 장애물 조각 생성 순, 인덱싱이 좌상단에서 우하단으로 되어있다.
				//마우스 피킹을 통해 배치 가능 불가능에 대한 조건 검사 시 장애물의 센터 조각 포지션(인덱스)와 보드의 피킹 된 인덱스를 통해 장애물의 다른 조각 포지션(인덱스)와 
				//보드의 다른 인덱스 조건 검사 쉽도록.

				//상대 보드는 내 보드 사이즈보고 위치 맞춰 줌
				ABoardPieceBase* pBoardPiece = Cast<ABoardPieceBase>(GET_MAINFRAMEWORK()->GetGameInstance()->GetWorld()->SpawnActor(pClass));
				if (pBoardPiece)
				{
					FVector Location = FVector(pBoardPiece->GetSizeX() * j, pBoardPiece->GetSizeY() * i * -1, 0.0f); //보드 높이값 0으로. 혹시 아닐수 있으면 변경

					//상대 보드는 내 보드 상단에 배치
					if (_bIsMineBorad == false)
					{
						Location += FVector(0, pBoardPiece->GetSizeY() * in_Y + 500, 0);
					}

					pBoardPiece->SetActorLocation(Location);

					pBoardPiece->Init(this, BoardIndex++);
					_BoardPiceList.Add(pBoardPiece);

				}
			}
		}
	}
}
