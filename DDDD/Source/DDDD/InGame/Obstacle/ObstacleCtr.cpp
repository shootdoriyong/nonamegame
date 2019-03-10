#include "ObstacleCtr.h"
#include "Obstacle.h"
#include "DefineMacro.h"

void UObstacleCtr::Init()
{
	_eCurrentObstacleType = EOBSTACLE_TYPE::NONE;
	_pObstacleList.Empty();
	_ObstacleTypeList.Empty();
	_CurrentObstacleArrangementCount = 0;
}

void UObstacleCtr::Update(float in_DeltaTime)
{
	if (IS_VALID(_pCurrentObstacle))
	{
		_pCurrentObstacle->Update(in_DeltaTime);
	}
}

void UObstacleCtr::Shutdown()
{
	if (IS_VALID(_pCurrentObstacle))
	{
		_pCurrentObstacle = nullptr;
	}

	for (auto Iter = _pObstacleList.CreateIterator(); Iter; ++Iter)
	{
		Iter->Value->Shutdown();
		Iter->Value = nullptr;
	}

	_pObstacleList.Empty();
	_ObstacleTypeList.Empty();
}

//************************************
// Date:	  2019/03/07
// Author:    Kimguhyun
// Method:    SetObstacleList
// Access:    public 
// Returns:   void
// Desc: ���ʿ� N���� ��ֹ� Ÿ���� ���� �س��� �뵵. �ӽ÷� enum �� ������ 3�� �־���� //��¥�� �������ΰŶ� UI�� �����ִ°� ū�ǹ̴� ��������.. ���� �������� �߰� �ɼ��� ������.
//************************************
void UObstacleCtr::SetObstacleList()
{
	for (int32 i = (int32)EOBSTACLE_TYPE::NONE + 1 ; i < (int32)EOBSTACLE_TYPE::MAX_SIZE; i++)
	{
		if(_ObstacleTypeList.Num() == COUNT_SHOW_OBSTACLE)
			break;

		if (_ObstacleTypeList.Num() == 0)
			_eCurrentObstacleType = (EOBSTACLE_TYPE)i;

		_ObstacleTypeList.Add((EOBSTACLE_TYPE)i);
	}

	//�׳� �ٷ� ����. ���� ��ġ ��ư ������ ��ֹ��� ����ٰų� �ϸ� �ɵ�
	CreateObstacle();
}


//************************************
// Date:	  2019/03/07
// Author:    Kimguhyun
// Method:    SelectedNextObstacle
// Access:    public 
// Returns:   void
// Desc: ���� ��ֹ��� ��ġ �Ϸ� �ϸ� �Ʒ� �Լ� �����༭ ����Ʈ ���� ��ϲ��� ���� ��ֹ��� ����
//************************************
void UObstacleCtr::SelectedNextObstacle()
{
	_CurrentObstacleArrangementCount++;
	//��ֹ� ��Ͽ��� ���� ��ֹ��� �����̸��� 0��°�ε��� = ���� ��ֹ�
	//���� ��ֹ� ������ ����
	_ObstacleTypeList.RemoveAt(0);
	
	//���� ��ֹ��� ���� ��ֹ��� ����
	_eCurrentObstacleType = _ObstacleTypeList[0];

	//��ֹ� ��Ͽ� �ϳ� �� �߰�
	EOBSTACLE_TYPE eLastObstacleType = _ObstacleTypeList[_ObstacleTypeList.Num() - 1];

	if ((int32)eLastObstacleType + 1 == (int32)EOBSTACLE_TYPE::MAX_SIZE)
	{
		_ObstacleTypeList.Add((EOBSTACLE_TYPE)((int32)EOBSTACLE_TYPE::NONE + 1));
	}
	else
	{
		_ObstacleTypeList.Add((EOBSTACLE_TYPE)((int32)eLastObstacleType + 1));
	}
}

EOBSTACLE_TYPE UObstacleCtr::GetSelectedCurrentObstacleType()
{
	return _eCurrentObstacleType;
}

void UObstacleCtr::CreateObstacle()
{
	if (IS_VALID(_pCurrentObstacle))
	{
		_pCurrentObstacle = nullptr;
	}

	_pCurrentObstacle = NewObject<UObstacle>();
	_pCurrentObstacle->Init(_CurrentObstacleArrangementCount);

	_pCurrentObstacle->CreateObstacle(_eCurrentObstacleType);

	_pObstacleList.Add(_CurrentObstacleArrangementCount, _pCurrentObstacle);
}

void UObstacleCtr::ArrangementObstacle()
{
	if (IS_VALID(_pCurrentObstacle))
	{
		_pCurrentObstacle->Arrangement();
		_pCurrentObstacle = nullptr;

		//�ϴ� ��ġ�ϸ� �ٷ� ���� ��ֹ� ����
		SelectedNextObstacle();
		CreateObstacle();
	}
}

bool UObstacleCtr::IsAvailabilityArrangement()
{
	if (IS_VALID(_pCurrentObstacle))
	{
		return _pCurrentObstacle->IsAvailabilityArrangement();
	}

	return false;
}