#pragma once

#include "InGameDefine.generated.h"

UENUM(Blueprintable)
enum class EOBSTACLE_TYPE : uint8
{
	NONE,

	//�̸� �����.. �ϴ� ���Ƿ�
	POLYMINO_1, // ��
	POLYMINO_2,	// �� 
	POLYMINO_3,	// ��
	POLYMINO_4, // ��
	POLYMINO_5, // s
	POLYMINO_6, // ��
	POLYMINO_7, // J
	POLYMINO_8, // ��
	POLYMINO_9, // ��
	POLYMINO_10, // ��
	POLYMINO_11, // ��
	POLYMINO_12, // ��
	POLYMINO_13, // ��

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
	
	HIDDEN, //���忡 ���콺�� ����� Hidden ���·� // ObstacleState�� Hidden�϶� ��� ���� ObstaclePiece�� Hidden�� �ȴ�.
	PREVIEW, //��ġ �� �̸����� ������ ��ֹ� ����
	ARRANGEMENT_IMPOSSIBLE, //��ġ �� �̸����� ���� �� �� �ش� ��ֹ� ������ ��ġ �Ұ��� �� // ��ġ ���� �ϸ� �׳� Preview ���·� �θ� �ȴ�.

	ARRANGEMENT, //��ġ(��ġ) ����

	MAX_SIZE,
};

UENUM(Blueprintable)
enum class EBOARD_PIECE_STATE_TYPE : uint8
{
	NONE,

	UNDER_PAWN,
	UNDER_OBSTACLE,

	MAX_SIZE,
};