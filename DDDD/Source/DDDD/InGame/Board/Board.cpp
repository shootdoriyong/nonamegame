// Fill out your copyright notice in the Description page of Project Settings.

#include "Board.h"
#include "BoardPieceBase.h"
#include "BoardPieceNormal.h"
#include "DefineMacro.h"

void UBoard::Init()
{
	_BoardPieceMap.Empty();

	_bIsMineBorad = false;
}

void UBoard::Update(float in_DeltaTime)
{

}

void UBoard::Shutdown()
{
	for (auto Iter = _BoardPieceMap.CreateIterator(); Iter; ++Iter)
	{
		Iter->Value->Destroy();
	}

	_BoardPieceMap.Empty();
}

void UBoard::CreateBoard(bool in_bIsMine, int32 in_X, int32 in_Y)
{
	_bIsMineBorad = in_bIsMine;

	int32 BoardIndex = 0;

	for (int32 i = 0; i < in_X; i++)
	{
		for (int32 j = 0; j < in_Y; j++)
		{
			//�ϴ� Normal Board �������θ� Board ��������
			UClass* pClass = nullptr;
			FString strBPPath = "/Game/Board/BoardNormalPiece.BoardNormalPiece_C";

			pClass = Cast<UClass>(StaticLoadClass(ABoardPieceNormal::StaticClass(), NULL, *strBPPath));

			if (pClass != nullptr)
			{
				//�� ���� , �� ���� ������ġ ����. ���� ���� ũ�� ��� ���� �־� �ϴ� ���� �� �ְ�

				///�� ���� ���ϴ� ���� ����. 0, 0, 0�� ��������. ����(�ε���) ���� = ���ϴ� -> ���� ������
				//19.03.08 �� ���� ������ �»�� ���� �� �ϴ� ������ �����ǵ���. ��? ��ֹ� ������ ��ֹ� ���� ���� ��, �ε����� �»�ܿ��� ���ϴ����� �Ǿ��ִ�.
				//���콺 ��ŷ�� ���� ��ġ ���� �Ұ��ɿ� ���� ���� �˻� �� ��ֹ��� ���� ���� ������(�ε���)�� ������ ��ŷ �� �ε����� ���� ��ֹ��� �ٸ� ���� ������(�ε���)�� 
				//������ �ٸ� �ε��� ���� �˻� ������.

				//��� ����� �� ���� ������� ��ġ ���� ��
				ABoardPieceBase* pBoardPiece = Cast<ABoardPieceBase>(GET_MAINFRAMEWORK()->GetGameInstance()->GetWorld()->SpawnActor(pClass));
				if (pBoardPiece)
				{
					FVector Location = FVector(pBoardPiece->GetSizeX() * i * -1, pBoardPiece->GetSizeY() * j, 0.0f); //���� ���̰� 0����. Ȥ�� �ƴҼ� ������ ����

					//��� ����� �� ���� ��ܿ� ��ġ
					if (_bIsMineBorad == false)
					{
						Location += FVector(0, pBoardPiece->GetSizeY() * in_Y + 500, 0);
					}

					pBoardPiece->SetActorLocation(Location);

					_BoardPieceMap.Add(BoardIndex, pBoardPiece);
					pBoardPiece->Init(this, BoardIndex++);
				}
			}
		}
	}
}

bool UBoard::IsMineBoard()
{
	return _bIsMineBorad;
}


bool UBoard::GetBoardPieceState(int32 in_BardPieceIndex, EBOARD_PIECE_STATE_TYPE& out_eBoardPieceState)
{
	auto FindIter = _BoardPieceMap.Find(in_BardPieceIndex);

	if (FindIter)
	{
		out_eBoardPieceState = (*FindIter)->GetState();
		return true;
	}
	
	return false;
}

 bool UBoard::SetBoardPieceState(int32 in_BardPieceIndex, EBOARD_PIECE_STATE_TYPE in_eBoardPieceState)
{
	 auto FindIter = _BoardPieceMap.Find(in_BardPieceIndex);

	 if (FindIter)
	 {
		 (*FindIter)->SetState(in_eBoardPieceState);
		 return true;
	 }

	 return false;
}

 ABoardPieceBase* UBoard::GetBoardPiece(int32 in_BaordPieceIndex)
 {
	 auto FindIter = _BoardPieceMap.Find(in_BaordPieceIndex);

	 return *FindIter;
 }