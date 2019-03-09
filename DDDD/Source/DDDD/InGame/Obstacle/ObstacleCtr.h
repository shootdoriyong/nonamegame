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
	//���� ���� �� ��ֹ� Ÿ��. (��ֹ� Ÿ���� �����ϴ°Ծƴ϶� ���������� ���� �� Ÿ���� �����޴´ٰ��Ѵ�)
	EOBSTACLE_TYPE			_eCurrentObstacleType;

	//���� ������ ��ֹ� Ÿ�԰� ���� ������ ��ֹ� Ÿ�� ����Ʈ�� ������ �ִ´�. �� ����� UI�� �����ִ��� �ϸ�ɵ�
	TArray<EOBSTACLE_TYPE>	_ObstacleTypeList;

	UPROPERTY()
	UObstacle*				_pCurrentObstacle;

	UPROPERTY()
	TMap<int32, UObstacle*>	_pObstacleList; //��ġ ������ ��ֹ��� ������ ����. ���� �ʿ� �� ����

	int32					_CurrentObstacleArrangementCount;
};
