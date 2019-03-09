#include "Obstacle.h"
#include "ObstaclePieceBase.h"
#include "ObstaclePieceNormal.h"
#include "DefineMacro.h"
#include "ObstaclePieceGroup.h"
#include "DDDDPlayerController.h"
#include "BoardPieceBase.h"

void UObstacle::Init(int32 in_ArrangementCountIndex)
{
	_pObstacleGroupingActor = nullptr;

	_ObstaclePieceMap.Empty();
	_ArrangementCountIndex = in_ArrangementCountIndex;

	_ObstacleInitInfoMap.Empty();

	_ObstacleStateType = EOBSTACLE_STATE_TYPE::NONE;

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
}

void UObstacle::Update(float in_DeltaTime)
{
	if (IS_VALID(_pObstacleGroupingActor))
	{
		ADDDDPlayerController*pPC = Cast<ADDDDPlayerController>(GET_MAINFRAMEWORK()->GetGameInstance()->GetWorld()->GetFirstPlayerController());

		if (IS_VALID(pPC))
		{
			FHitResult Hit;
			if(pPC->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, true, Hit))
			{
				ABoardPieceBase* pHitBoard = Cast<ABoardPieceBase>(Hit.GetActor());
				if (IS_VALID(pHitBoard))
				{
					FVector NewLocation = pHitBoard->GetActorLocation();
					NewLocation.Z = _pObstacleGroupingActor->GetActorLocation().Z;
					_pObstacleGroupingActor->SetActorLocation(NewLocation);
				}
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

	if (!IS_VALID(_pObstacleGroupingActor))
		return;

	_pObstacleGroupingActor->SetActorHiddenInGame(true);
	_pObstacleGroupingActor->SetActorLocation(FVector::ZeroVector);
	_pObstacleGroupingActor->SetActorLabel("ObstaclGroup");

	auto FindIter = _ObstacleInitInfoMap.Find(in_eObstacleType);

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
					int32 CenterPieceIndex = GetCeneterPieceIndex(in_eObstacleType);
					FVector CenterOffsetVector = FVector(CenterPieceIndex/ 4 * -SizeX, CenterPieceIndex % 4 * SizeY, 0);
					CenterOffsetVector *= -1;

					FTransform TR;
					TR.SetLocation(CenterOffsetVector);

					pObstaclePiece->AddActorLocalTransform(TR);
				}
			}
		}
	}

	_ObstacleStateType = EOBSTACLE_STATE_TYPE::PREVIEW;


	_pObstacleGroupingActor->SetActorHiddenInGame(false);
}

EOBSTACLE_STATE_TYPE UObstacle::GetObstacleStateType()
{
	return _ObstacleStateType;
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