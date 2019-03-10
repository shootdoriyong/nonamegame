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

	//4x4 ���簢 �� ��������. 
	//4���� ������ ���� 0�� ����� 1�� ä���
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

	//�»�� ���� ���ϴ� ������ 0�̾ƴ� ��쿡 Piece�� �����.
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

	_eObstacleStateType = EOBSTACLE_STATE_TYPE::ARRANGEMENT;

	TArray<AActor*> ObstaclePieceList;
	_pObstacleGroupingActor->GetAttachedActors(ObstaclePieceList);

	for (int32 i = 0; i < ObstaclePieceList.Num(); i++)
	{
		AObstaclePieceBase* pOBP = Cast<AObstaclePieceBase>(ObstaclePieceList[i]);
		if (pOBP)
		{
			pOBP->SetState(EOBSTACLE_PIECE_STATE_TYPE::ARRANGEMENT);

			//�̹� �� �Լ����°� ��ü�� ��ġ�� ���� �� ���¶�� ���̴�.
			FHitResult Hit(ForceInit);
			FCollisionQueryParams Params = FCollisionQueryParams(FName(TEXT("Trace")), true, pOBP);

			FVector Start = pOBP->GetActorLocation();
			FVector End = pOBP->GetActorLocation().UpVector * -1 * 500; //500 ������ ���� ���� ���� ���� ����, ��ֹ� ���� ������ 1m (100)�� �̰ź��ٸ� ũ�� ���� �ɵ�
			Params.bTraceAsyncScene = true;
			//rams.bReturnPhysicalMaterial = true;

			bool Traced = GET_MAINFRAMEWORK()->GetGameInstance()->GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_GameTraceChannel1, Params);

			//��ġ�Ϸ��� ��ֹ� ���� �ؿ� ���� ���� �ִٸ� //���⼱ ������ �ִ� ��Ȳ�̾�� �Ѵ�.
			if (Traced)
			{
				ABoardPieceBase* pUnderBoard = Cast<ABoardPieceBase>(Hit.GetActor());
				if (pUnderBoard)
				{
					pUnderBoard->SetState(EBOARD_PIECE_STATE_TYPE::UNDER_OBSTACLE);
				}
			}
			else
			{
				check(false); //����� ������ �ȵ�. �ؿ� ���� �Ǵ� ���� ������ ���µ� �ش� �Լ��� Ÿ�� �ȵȴ�.
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

	TArray<AActor*> ObstaclePieceList;
	_pObstacleGroupingActor->GetAttachedActors(ObstaclePieceList);

	for (int32 i = 0; i < ObstaclePieceList.Num(); i++)
	{
		AObstaclePieceBase* pOBP = Cast<AObstaclePieceBase>(ObstaclePieceList[i]);
		if (pOBP)
		{
			FHitResult Hit(ForceInit);
			FCollisionQueryParams Params = FCollisionQueryParams(FName(TEXT("Trace")), true, pOBP);

			FVector Start = pOBP->GetActorLocation();
			FVector End = pOBP->GetActorLocation() + pOBP->GetActorLocation().UpVector * -1 * 500; //500 ������ ���� ���� ���� ���� ����, ��ֹ� ���� ������ 1m (100)�� �̰ź��ٸ� ũ�� ���� �ɵ�
			//Params.bTraceAsyncScene = true;
			//rams.bReturnPhysicalMaterial = true;

			bool Traced = GET_MAINFRAMEWORK()->GetGameInstance()->GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_GameTraceChannel1, Params);

			int32 aa = pOBP->GetObstaclePieceIndex();
			//��ġ�Ϸ��� ��ֹ� ���� �ؿ� ���� ���� �ִٸ�
			if (Traced)
			{
				ABoardPieceBase* pUnderBoard = Cast<ABoardPieceBase>(Hit.GetActor());
				int32 bb = pUnderBoard->GetBoardIndex();

				if (pUnderBoard)
				{
					//�̹� �ش� ���������� ��ֹ� �Ʒ� ���������̰ų� ��(ĳ����)�� ��ġ�� ���������̶��
					if (pUnderBoard->GetState() == EBOARD_PIECE_STATE_TYPE::UNDER_OBSTACLE ||
						pUnderBoard->GetState() == EBOARD_PIECE_STATE_TYPE::UNDER_PAWN)
					{
						pOBP->SetState(EOBSTACLE_PIECE_STATE_TYPE::PREVIEW_FAIL);
						UE_LOG(LogClass, Warning, TEXT("PREVIEW_FAIL 1 %d"), pOBP->GetObstaclePieceIndex());
					}
					else
					{
						pOBP->SetState(EOBSTACLE_PIECE_STATE_TYPE::PREVIEW);
						UE_LOG(LogClass, Warning, TEXT("PREVIEW %d"), pOBP->GetObstaclePieceIndex());
					}
				}
				else
				{
					pOBP->SetState(EOBSTACLE_PIECE_STATE_TYPE::PREVIEW_FAIL);
					UE_LOG(LogClass, Warning, TEXT("PREVIEW_FAIL 2 %d"), pOBP->GetObstaclePieceIndex());
				}
			}
			else
			{
				pOBP->SetState(EOBSTACLE_PIECE_STATE_TYPE::PREVIEW_FAIL);
				UE_LOG(LogClass, Warning, TEXT("PREVIEW_FAIL 3 %d"), pOBP->GetObstaclePieceIndex());
			}
		}
	}
}

//��ġ ���� ����
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
			if (pOBP->GetState() == EOBSTACLE_PIECE_STATE_TYPE::PREVIEW_FAIL) //�ϳ��� ��ֹ� �����̶� ��ġ �Ұ� ���¶��
				return false;
		}
	}

	return true;
}