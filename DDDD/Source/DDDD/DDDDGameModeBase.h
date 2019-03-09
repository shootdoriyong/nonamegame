// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DDDDGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DDDD_API ADDDDGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADDDDGameModeBase(const FObjectInitializer& ObjectInitializer);

public:
	virtual	void				BeginPlay() override;
};
