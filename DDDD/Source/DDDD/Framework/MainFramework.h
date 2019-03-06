// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DDDDGameInstance.h"
#include "MainFramework.generated.h"

/**
 * 
 */
class UInGameMng;
class UUIMng;
class ULobbyMng;
class UDataMng;

UCLASS()
class DDDD_API UMainFramework : public UObject
{
	GENERATED_BODY()
	
public:
	UMainFramework(const FObjectInitializer & ObjectInitializer);

	void						Init(UGameInstance* in_GameInstance);
	void						UpdateMainFramework(float in_DeltaSeconds);
	void						Shutdown();
private:
	UGameInstance * _pMainGameInstance;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInGameMng*				_pInGameMng;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUIMng*					_pUIMng;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULobbyMng*				_pLobbyMng;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataMng*				_pDataMng;

	UGameInstance*				GetGameInstance() { return _pMainGameInstance; };
};
