// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LobbyMng.generated.h"

/**
 * 
 */
UCLASS()
class DDDD_API ULobbyMng : public UObject
{
	GENERATED_BODY()
	
public:
	void					Init();
	void					Update(float in_DeltaTime);
	void					Shutdown();
	
	
};