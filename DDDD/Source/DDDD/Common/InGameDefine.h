#pragma once

#include "InGameDefine.generated.h"

UENUM(Blueprintable)
enum class EOBSTACLE_TYPE : uint8
{
	NONE,

	//이름 어쨰하지.. 일단 임의로
	POLYMINO_1, // ㅁ
	POLYMINO_2,	// ㅗ 
	POLYMINO_3,	// ㄱ
	POLYMINO_4, // ㅣ
	POLYMINO_5, // s
	POLYMINO_6, // ㅏ
	POLYMINO_7, // J
	POLYMINO_8, // ㅡ
	POLYMINO_9, // ㄹ
	POLYMINO_10, // ㅜ
	POLYMINO_11, // ㄴ
	POLYMINO_12, // ㅓ
	POLYMINO_13, // ┌

	MAX_SIZE,
};

UENUM(Blueprintable)
enum class EOBSTACLE_STATE_TYPE : uint8
{
	NONE,

	HIDDEN,
	PREVIEW,
	ARRANGEMENT,

	MAX_SIZE,
};

UENUM(Blueprintable)
enum class EOBSTACLE_PIECE_STATE_TYPE : uint8
{
	NONE,
	
	HIDDEN, //보드에 마우스가 벗어나면 Hidden 상태로 // ObstacleState가 Hidden일때 모든 종속 ObstaclePiece는 Hidden이 된다.
	PREVIEW, //설치 전 미리보기 상태의 장애물 조각
	PREVIEW_FAIL, //설치 전 미리보기 상태의 장애물 조각인데 해당 위치에 설치가 불가능 한 경우 일때( 해당 보드 위치에 캐릭터나 다른 장애물조각이 존재 등의 이유)

	ARRANGEMENT, //설치(배치) 상태

	MAX_SIZE,
};