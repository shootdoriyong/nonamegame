// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DDDDGameInstance.h"
#include "MainFramework.generated.h"

/**
 * 
 */
UCLASS()
class DDDD_API UMainFramework : public UObject
{
	GENERATED_BODY()
	

public:
	UMainFramework(const FObjectInitializer & ObjectInitializer);

	void						Init(UGameInstance* in_GameInstance);
	void						UpdateMainFramework(float in_DeltaSeconds);
	void						Shutdown();

	UGameInstance*				GetGameInstance() { return _pMainGameInstance; };
private:
	UGameInstance * _pMainGameInstance;
};
