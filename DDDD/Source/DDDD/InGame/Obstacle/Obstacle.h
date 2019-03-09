// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InGameDefine.h"
#include "Obstacle.generated.h"

/**
 *
 */

class AObstaclePieceBase;
class AObstaclePieceGroup;
UCLASS()
class DDDD_API UObstacle : public UObject
{
	GENERATED_BODY()

public:
	void					Init(int32 in_ArrangementCountIndex);
	void					Update(float in_DeltaTime);
	void					Shutdown();

	void					CreateObstacle(EOBSTACLE_TYPE in_eObstacleType);
	EOBSTACLE_STATE_TYPE	GetObstacleStateType();
private:
	int32					GetCeneterPieceIndex(EOBSTACLE_TYPE in_eObstacleType);
	AObstaclePieceGroup*	CreateObstacleGroupActor();
private:
	EOBSTACLE_TYPE			_eObstacleType;
	EOBSTACLE_STATE_TYPE	_ObstacleStateType;
	TMap<EOBSTACLE_TYPE, TArray<FString>> _ObstacleInitInfoMap;

	UPROPERTY()
	TMap<int32, AObstaclePieceBase*> _ObstaclePieceMap;

	int32					_ArrangementCountIndex;

	UPROPERTY()
	AActor*					_pObstacleGroupingActor;
};