// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InGameDefine.h"
#include "ObstacleCtr.generated.h"

/**
 *
 */

#define COUNT_SHOW_OBSTACLE 3

class UObstacle;

UCLASS()
class DDDD_API UObstacleCtr : public UObject
{
	GENERATED_BODY()

public:
	void					Init();
	void					Update(float in_DeltaTime);
	void					Shutdown();

	void					SetObstacleList();
	void					SelectedNextObstacle();
	EOBSTACLE_TYPE			GetSelectedCurrentObstacleType();

	void					CreateObstacle();
private:
	//현재 선택 된 장애물 타입. (장애물 타입은 선택하는게아니라 순차적으로 고정 된 타입을 배정받는다고한다)
	EOBSTACLE_TYPE			_eCurrentObstacleType;

	//현재 차례의 장애물 타입과 이후 차례의 장애물 타입 리스트를 가지고 있는다. 이 목록을 UI상에 보여주던지 하면될듯
	TArray<EOBSTACLE_TYPE>	_ObstacleTypeList;

	UPROPERTY()
	UObstacle*				_pCurrentObstacle;

	UPROPERTY()
	TMap<int32, UObstacle*>	_pObstacleList; //배치 순서와 장애물을 맵으로 저장. 추후 필요 할 수도

	int32					_CurrentObstacleArrangementCount;
};
