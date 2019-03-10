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
// Desc: 최초에 N개의 장애물 타입을 세팅 해놓는 용도. 임시로 enum 값 순으로 3개 넣어두자 //어짜피 순차적인거라 UI상에 보여주는게 큰의미는 없겟지만.. 추후 랜덤성이 추가 될수도 있으니.
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

	//그냥 바로 만듬. 추후 배치 버튼 누르면 장애물을 만든다거나 하면 될듯
	CreateObstacle();
}


//************************************
// Date:	  2019/03/07
// Author:    Kimguhyun
// Method:    SelectedNextObstacle
// Access:    public 
// Returns:   void
// Desc: 현재 장애물을 설치 완료 하면 아래 함수 콜해줘서 리스트 다음 목록껄로 현재 장애물로 변경
//************************************
void UObstacleCtr::SelectedNextObstacle()
{
	_CurrentObstacleArrangementCount++;
	//장애물 목록에는 현재 장애물도 포함이르모 0번째인덱스 = 현재 장애물
	//현재 장애물 썼으니 날림
	_ObstacleTypeList.RemoveAt(0);
	
	//다음 장애물을 현재 장애물로 세팅
	_eCurrentObstacleType = _ObstacleTypeList[0];

	//장애물 목록에 하나 더 추가
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

		//일단 배치하면 바로 다음 장애물 생성
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