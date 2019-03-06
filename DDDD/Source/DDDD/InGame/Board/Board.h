// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Board.generated.h"

/**
 * 
 */

class ABoardPieceBase;

UCLASS()
class DDDD_API UBoard : public UObject
{
	GENERATED_BODY()
	
public:
	void					Init();
	void					Update(float in_DeltaTime);
	void					Shutdown();

	void					CreateBoard(bool in_bIsMine, int32 in_X, int32 in_Y);

private:
	//���� ���� �ε����� ������ �����ϴ°� ���Ҽ���. �ϴ� ������ ���� �ε��� �����Ŷ� ��̷� ����
	UPROPERTY()
	TArray<ABoardPieceBase*> _BoardPiceList;

private:
	bool					_bIsMineBorad;
};
