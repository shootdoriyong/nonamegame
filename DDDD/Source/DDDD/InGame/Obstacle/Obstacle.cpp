#include "Obstacle.h"
#include "ObstaclePieceBase.h"
#include "ObstaclePieceNormal.h"
#include "DefineMacro.h"
#include "ObstaclePieceGroup.h"
#include "DDDDPlayerController.h"
#include "BoardPieceBase.h"
#include "InGameMng.h"
#include "Board.h"
#include "BoardCtr.h"

void UObstacle::Init(int32 in_ArrangementCountIndex)
{
	_pObstacleGroupingActor = nullptr;

	_ObstaclePieceMap.Empty();
	_ArrangementCountIndex = in_ArrangementCountIndex;

	_ObstacleInitInfoMap.Empty();

	_eObstacleStateType = EOBSTACLE_STATE_TYPE::NONE;

	//4x4 정사각 형 기준으로. 
	//4개씩 위에서 부터 0은 비었고 1은 채우고
	{
		TArray<FString> Info = { "0","0","0","0",
								"0","1","C","0",
								"0","1","1","0",
								"0","0","0","0"};
		_ObstacleInitInfoMap.Add(EOBSTACLE_TYPE::POLYMINO_1, Info);
	}
	{
		TArray<FString> Info = { "0","0","0","0",
								"0","1","0","0",
								"1","C","1","0",
								"0","0","0","0" };
		_ObstacleInitInfoMap.Add(EOBSTACLE_TYPE::POLYMINO_2, Info);
	}
	{
		TArray<FString> Info = { "0","0","0","0",
								"1","1","C","0",
								"0","0","1","0",
								"0","0","0","0" };
		_ObstacleInitInfoMap.Add(EOBSTACLE_TYPE::POLYMINO_3, Info);
	}
	{
		TArray<FString> Info = { "0","1","0","0",
								"0","1","0","0",
								"0","C","0","0",
								"0","1","0","0" };
		_ObstacleInitInfoMap.Add(EOBSTACLE_TYPE::POLYMINO_4, Info);
	}
	{
		TArray<FString> Info = { "0","0","0","0",
								"0","C","1","0",
								"1","1","0","0",
								"0","0","0","0" };
		_ObstacleInitInfoMap.Add(EOBSTACLE_TYPE::POLYMINO_5, Info);
	}
	{
		TArray<FString> Info = { "0","0","0","0",
								"0","1","0","0",
								"0","C","1","0",
								"0","1","0","0" };
		_ObstacleInitInfoMap.Add(EOBSTACLE_TYPE::POLYMINO_6, Info);
	}
	{
		TArray<FString> Info = { "0","0","1","0",
								"0","0","1","0",
								"0","1","C","0",
								"0","0","0","0" };
		_ObstacleInitInfoMap.Add(EOBSTACLE_TYPE::POLYMINO_7, Info);
	}
	{
		TArray<FString> Info = { "0","0","0","0",
								"1","1","C","1",
								"0","0","0","0"
								"0","0","0","0" };
		_ObstacleInitInfoMap.Add(EOBSTACLE_TYPE::POLYMINO_8, Info);
	}
	{
		TArray<FString> Info = { "0","1","0","0",
								"0","C","1","0",
								"0","0","1","0",
								"0","0","0","0" };
		_ObstacleInitInfoMap.Add(EOBSTACLE_TYPE::POLYMINO_9, Info);
	}
	{
		TArray<FString> Info = { "0","0","0","0",
								"0","0","0","0",
								"1","C","1","0",
								"0","1","0","0" };
		_ObstacleInitInfoMap.Add(EOBSTACLE_TYPE::POLYMINO_10, Info);
	}
	{
		TArray<FString> Info = { "0","0","0","0",
								"0","1","0","0",
								"0","C","1","1",
								"0","0","0","0" };
		_ObstacleInitInfoMap.Add(EOBSTACLE_TYPE::POLYMINO_11, Info);
	}
	{
		TArray<FString> Info = { "0","0","0","0",
								"0","1","0","0",
								"1","C","0","0",
								"0","1","0","0" };
		_ObstacleInitInfoMap.Add(EOBSTACLE_TYPE::POLYMINO_12, Info);
	}
	{
		TArray<FString> Info = { "0","0","0","0",
								"0","C","1","0",
								"0","1","0","0",
								"0","1","0","0" };
		_ObstacleInitInfoMap.Add(EOBSTACLE_TYPE::POLYMINO_13, Info);
	}

	_pUnderCursorBoard = nullptr;
}

void UObstacle::Update(float in_DeltaTime)
{
	if (IS_VALID(_pObstacleGroupingActor) && _eObstacleStateType != EOBSTACLE_STATE_TYPE::ARRANGEMENT)
	{
		ADDDDPlayerController*pPC = Cast<ADDDDPlayerController>(GET_MAINFRAMEWORK()->GetGameInstance()->GetWorld()->GetFirstPlayerController());

		if (IS_VALID(pPC))
		{
			FHitResult Hit;
			if(pPC->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, true, Hit))
			{
				TArray<AActor*> ObstaclePieceList;
				_pObstacleGroupingActor->GetAttachedActors(ObstaclePieceList);

				for (int32 i = 0; i < ObstaclePieceList.Num(); i++)
				{
					if(ObstaclePieceList[i]->bHidden == true)
						ObstaclePieceList[i]->SetActorHiddenInGame(false);
				}

				ABoardPieceBase* pHitBoard = Cast<ABoardPieceBase>(Hit.GetActor());
				if (IS_VALID(pHitBoard))
				{
					int32 HitBoardIndex = pHitBoard->GetBoardIndex();

					FVector NewLocation = pHitBoard->GetActorLocation();
					NewLocation.Z = _pObstacleGroupingActor->GetActorLocation().Z;
					_pObstacleGroupingActor->SetActorLocation(NewLocation);

					//if (!IS_VALID(_pUnderCursorBoard))
					{
						_pUnderCursorBoard = pHitBoard;
						UpdateObstaclePieceState();
					}
				}
			}
			else
			{
				TArray<AActor*> ObstaclePieceList;
				_pObstacleGroupingActor->GetAttachedActors(ObstaclePieceList);

				for (int32 i = 0; i < ObstaclePieceList.Num(); i++)
				{
					if (ObstaclePieceList[i]->bHidden == false)
						ObstaclePieceList[i]->SetActorHiddenInGame(true);
				}

				if (IS_VALID(_pUnderCursorBoard))
					_pUnderCursorBoard = nullptr;
			}
		}
	}
}

void UObstacle::Shutdown()
{
	for (auto Iter = _ObstaclePieceMap.CreateIterator(); Iter; ++Iter)
	{
		Iter->Value->Destroy();
		Iter->Value = nullptr;
	}

	_ObstaclePieceMap.Empty();

	if (IS_VALID(_pObstacleGroupingActor))
	{
		_pObstacleGroupingActor->Destroy();
		_pObstacleGroupingActor = nullptr;
	}

	_ObstacleInitInfoMap.Empty();
}

void UObstacle::CreateObstacle(EOBSTACLE_TYPE in_eObstacleType)
{
	_pObstacleGroupingActor = CreateObstacleGroupActor();
	_eObstacleType = in_eObstacleType;

	if (!IS_VALID(_pObstacleGroupingActor))
		return;

	_pObstacleGroupingActor->SetActorHiddenInGame(true);
	_pObstacleGroupingActor->SetActorLocation(FVector::ZeroVector);
	_pObstacleGroupingActor->SetActorLabel("ObstaclGroup");

	auto FindIter = _ObstacleInitInfoMap.Find(_eObstacleType);

	TArray<FString> ObstacleInfoList = *FindIter;

	//좌상단 부터 우하단 순으로 0이아닌 경우에 Piece를 만든다.
	for (int32 i = 0; i < ObstacleInfoList.Num(); i++)
	{
		if (ObstacleInfoList[i] != "0")
		{
			UClass* pClass = nullptr;
			FString strBPPath = "/Game/Obstacle/ObstacleNormalPiece.ObstacleNormalPiece_C";

			pClass = Cast<UClass>(StaticLoadClass(AObstaclePieceNormal::StaticClass(), NULL, *strBPPath));

			if (pClass != nullptr)
			{
				AObstaclePieceBase* pObstaclePiece = Cast<AObstaclePieceBase>(GET_MAINFRAMEWORK()->GetGameInstance()->GetWorld()->SpawnActor(pClass));
				if (pObstaclePiece)
				{
					_ObstaclePieceMap.Add(i, pObstaclePiece);

					pObstaclePiece->Init(i);
					pObstaclePiece->SetState(EOBSTACLE_PIECE_STATE_TYPE::PREVIEW);

					float SizeX = pObstaclePiece->GetSizeX();
					float SizeY = pObstaclePiece->GetSizeY();
					float SizeZ = pObstaclePiece->GetSizeZ();

					FVector Location = FVector(i / 4 * -SizeX, i % 4 * SizeY, SizeZ);

					pObstaclePiece->SetActorLocation(Location);
					pObstaclePiece->AttachToActor(_pObstacleGroupingActor, FAttachmentTransformRules::KeepRelativeTransform);
					int32 CenterPieceIndex = GetCeneterPieceIndex(_eObstacleType);
					FVector CenterOffsetVector = FVector(CenterPieceIndex/ 4 * -SizeX, CenterPieceIndex % 4 * SizeY, 0);
					CenterOffsetVector *= -1;

					FTransform TR;
					TR.SetLocation(CenterOffsetVector);

					pObstaclePiece->AddActorLocalTransform(TR);
				}
			}
		}
	}

	_eObstacleStateType = EOBSTACLE_STATE_TYPE::PREVIEW;


	_pObstacleGroupingActor->SetActorHiddenInGame(false);
}

void UObstacle::Arrangement()
{
	if (!IS_VALID(_pObstacleGroupingActor))
		return;

	if (!IS_VALID(_pUnderCursorBoard))
		return;

	int32 UnderCursorBoardIndex = _pUnderCursorBoard->GetBoardIndex();
	int32 CenterObstaclePieceIndex = GetCeneterPieceIndex(_eObstacleType);

	//좌상단부터 우하단 순으로 장애물을 그릴 때 2차원 배열 구조체 상의 해당 조각 인덱스의 위치 인덱스 값.
	//여기서 4는 장애물이 4x4로 이루어져있어서.
	FVector2D CenterObstaclePieceIndexInfo = FVector2D(CenterObstaclePieceIndex / 4, CenterObstaclePieceIndex % 4);

	TArray<AActor*> ObstaclePieceList;
	_pObstacleGroupingActor->GetAttachedActors(ObstaclePieceList);

	for (int32 i = 0; i < ObstaclePieceList.Num(); i++)
	{
		AObstaclePieceBase* pOBP = Cast<AObstaclePieceBase>(ObstaclePieceList[i]);
		if (pOBP)
		{
			pOBP->SetState(EOBSTACLE_PIECE_STATE_TYPE::ARRANGEMENT);

			int32 CurrentObstaclePieceIndex = pOBP->GetObstaclePieceIndex();
			FVector2D CurrentObstaclePieceIndexInfo = FVector2D(CurrentObstaclePieceIndex / 4, CurrentObstaclePieceIndex % 4);

			FVector2D ObstaclePieceInfoOffset = CurrentObstaclePieceIndexInfo - CenterObstaclePieceIndexInfo;


			int32 CurrentObstaclePieceMatchBoardIndex = UnderCursorBoardIndex + (ObstaclePieceInfoOffset.X * BOARD_X) + ObstaclePieceInfoOffset.Y;

			ABoardPieceBase* pBoardPiece = _pUnderCursorBoard->GetOwnerBoard()->GetBoardPiece(CurrentObstaclePieceMatchBoardIndex);

			if (pBoardPiece)
			{
				pBoardPiece->SetState(EBOARD_PIECE_STATE_TYPE::UNDER_OBSTACLE);
			}
		}
	}
}

EOBSTACLE_STATE_TYPE UObstacle::GetObstacleStateType()
{
	return _eObstacleStateType;
}

int32 UObstacle::GetCeneterPieceIndex(EOBSTACLE_TYPE in_eObstacleType)
{
	auto FindIter = _ObstacleInitInfoMap.Find(in_eObstacleType);

	if (FindIter)
	{
		TArray<FString> Info = *FindIter;

		for (int32 i = 0; i < Info.Num(); i++)
		{
			if (Info[i] == "C")
				return i;
		}
	}

	UE_LOG(LogClass, Error, TEXT("Cant`Find Ceneter In ObstaclePiece"));
	check(false);
	return 0;
}

AObstaclePieceGroup* UObstacle::CreateObstacleGroupActor()
{
	UClass* pClass = nullptr;
	FString strBPPath = "/Game/Obstacle/ObstacleGroup.ObstacleGroup_C";

	pClass = Cast<UClass>(StaticLoadClass(AObstaclePieceGroup::StaticClass(), NULL, *strBPPath));

	if (pClass != nullptr)
	{
		return Cast<AObstaclePieceGroup>(GET_MAINFRAMEWORK()->GetGameInstance()->GetWorld()->SpawnActor(pClass));
	}

	return nullptr;
}

void UObstacle::UpdateObstaclePieceState()
{
	if (!IS_VALID(_pUnderCursorBoard))
		return;

	if (_eObstacleType == EOBSTACLE_TYPE::NONE)
		return;

	int32 UnderCursorBoardIndex = _pUnderCursorBoard->GetBoardIndex();
	int32 CenterObstaclePieceIndex = GetCeneterPieceIndex(_eObstacleType);

	//좌상단부터 우하단 순으로 장애물을 그릴 때 2차원 배열 구조체 상의 해당 조각 인덱스의 위치 인덱스 값.
	//여기서 4는 장애물이 4x4로 이루어져있어서.
	FVector2D CenterObstaclePieceIndexInfo = FVector2D(CenterObstaclePieceIndex / 4, CenterObstaclePieceIndex % 4);

	TArray<AActor*> ObstaclePieceList;
	_pObstacleGroupingActor->GetAttachedActors(ObstaclePieceList);

	for (int32 i = 0; i < ObstaclePieceList.Num(); i++)
	{
		AObstaclePieceBase* pOBP = Cast<AObstaclePieceBase>(ObstaclePieceList[i]);
		if (pOBP)
		{
			int32 CurrentObstaclePieceIndex = pOBP->GetObstaclePieceIndex();
			FVector2D CurrentObstaclePieceIndexInfo = FVector2D(CurrentObstaclePieceIndex / 4, CurrentObstaclePieceIndex % 4);

			FVector2D ObstaclePieceInfoOffset = CurrentObstaclePieceIndexInfo - CenterObstaclePieceIndexInfo;

			
			int32 CurrentObstaclePieceMatchXBoardIndex = UnderCursorBoardIndex + (ObstaclePieceInfoOffset.X * BOARD_X);

			//X 체크 //X 인덱스가 보드 최대 인덱스 보다 크거나 0보다 작으면 배치 불가다.
			if (CurrentObstaclePieceMatchXBoardIndex >= (BOARD_X * BOARD_Y) ||
				CurrentObstaclePieceMatchXBoardIndex < 0)
			{
				pOBP->SetState(EOBSTACLE_PIECE_STATE_TYPE::ARRANGEMENT_IMPOSSIBLE);
			}
			//Y 체크
			else if (CurrentObstaclePieceMatchXBoardIndex % BOARD_X == 0 && ObstaclePieceInfoOffset.Y < 0)
			{
				pOBP->SetState(EOBSTACLE_PIECE_STATE_TYPE::ARRANGEMENT_IMPOSSIBLE);
			}
			else if (CurrentObstaclePieceMatchXBoardIndex % BOARD_X - 1 == 0 && ObstaclePieceInfoOffset.Y > 0)
			{
				pOBP->SetState(EOBSTACLE_PIECE_STATE_TYPE::ARRANGEMENT_IMPOSSIBLE);
			}
			else
			{
				int32 CurrentObstaclePieceMatchBoardIndex = CurrentObstaclePieceMatchXBoardIndex + ObstaclePieceInfoOffset.Y;

				EBOARD_PIECE_STATE_TYPE BoardPieceState;
				if (_pUnderCursorBoard->GetOwnerBoard()->GetBoardPieceState(CurrentObstaclePieceMatchBoardIndex, BoardPieceState))
				{
					if(BoardPieceState == EBOARD_PIECE_STATE_TYPE::NONE)
						pOBP->SetState(EOBSTACLE_PIECE_STATE_TYPE::PREVIEW);
					else
						pOBP->SetState(EOBSTACLE_PIECE_STATE_TYPE::ARRANGEMENT_IMPOSSIBLE);
				}
				else
				{
					pOBP->SetState(EOBSTACLE_PIECE_STATE_TYPE::ARRANGEMENT_IMPOSSIBLE);
				}
			}
		}
	}
}

//배치 가능 여부
bool UObstacle::IsAvailabilityArrangement()
{
	if (!IS_VALID(_pObstacleGroupingActor))
		return false;

	TArray<AActor*> ObstaclePieceList;
	_pObstacleGroupingActor->GetAttachedActors(ObstaclePieceList);

	for (int32 i = 0; i < ObstaclePieceList.Num(); i++)
	{
		AObstaclePieceBase* pOBP = Cast<AObstaclePieceBase>(ObstaclePieceList[i]);
		if (pOBP)
		{
			if (pOBP->GetState() == EOBSTACLE_PIECE_STATE_TYPE::ARRANGEMENT_IMPOSSIBLE) //하나의 장애물 조각이라도 배치 불가 상태라면
				return false;
		}
	}

	return true;
}