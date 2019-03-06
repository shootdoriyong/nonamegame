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
			//�ϴ� Normal Board �������θ� Board ��������
			UClass* pClass = nullptr;
			FString strBPPath = "/Game/Board/BoardNormalPiece.BoardNormalPiece_C";

			pClass = Cast<UClass>(StaticLoadClass(ABoardPieceNormal::StaticClass(), NULL, *strBPPath));

			if (pClass != nullptr)
			{
				//�� ���� , �� ���� ������ġ ����. ���� ���� ũ�� ��� ���� �־� �ϴ� ���� �� �ְ�

				//�� ���� ���ϴ� ���� ����. 0, 0, 0�� ��������. ����(�ε���) ���� = ���ϴ� -> ���� ������
				//��� ����� �� ���� ������� ��ġ ���� ��
				ABoardPieceBase* pBoardPiece = Cast<ABoardPieceBase>(GET_MAINFRAMEWORK()->GetGameInstance()->GetWorld()->SpawnActor(pClass));
				if (pBoardPiece)
				{
					FVector Location = FVector(pBoardPiece->GetMeshSizeX() * j, pBoardPiece->GetMeshSizeY() * i, 0.0f); //���� ���̰� 0����. Ȥ�� �ƴҼ� ������ ����

					//��� ����� �� ���� ��ܿ� ��ġ
					if (_bIsMineBorad == false)
					{
						Location += FVector(0, pBoardPiece->GetMeshSizeY() * in_Y + 500, 0);
					}

					pBoardPiece->SetActorLocation(Location);

					pBoardPiece->Init(BoardIndex++);
					_BoardPiceList.Add(pBoardPiece);

				}
			}
		}
	}
}
