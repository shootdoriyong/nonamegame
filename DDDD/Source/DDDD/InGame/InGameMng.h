// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InGameMng.generated.h"

/**
 * 
 */
UCLASS()
class DDDD_API UInGameMng : public UObject
{
	GENERATED_BODY()
	
public:
	void					Init();
	void					Update(float in_DeltaTime);
	void					Shutdown();
	
	//인게임으로 넘어올 때 호출
	void					Enter();

	//실제 게임 시작 시 호출
	void					StartGame();
};
