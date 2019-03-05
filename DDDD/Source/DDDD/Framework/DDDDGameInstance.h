// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Containers/Ticker.h"
#include "DDDDGameInstance.generated.h"

/**
 * 
 */
class FDelegateHandle;

UCLASS()
class DDDD_API UDDDDGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	virtual void Shutdown() override;

	virtual void StartGameInstance();
#if WITH_EDITOR
	virtual FGameInstancePIEResult StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params) override;
#endif
	bool Tick(float in_DeltaSeconds);

private:
	FTickerDelegate _TickDelegate;
	FDelegateHandle _TickDelegateHandle;

private:
	void StartGame();

	void StopTick();
	
	
};
