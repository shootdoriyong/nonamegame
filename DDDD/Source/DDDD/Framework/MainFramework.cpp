// Fill out your copyright notice in the Description page of Project Settings.

#include "MainFramework.h"
#include "DefineMacro.h"
#include "InGameMng.h"
#include "LobbyMng.h"
#include "UIMng.h"
#include "DataMng.h"

UMainFramework::UMainFramework(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UMainFramework::Init(UGameInstance* in_GameInstance)
{
	_pMainGameInstance = in_GameInstance;

	_pUIMng = NewObject<UUIMng>();
	_pLobbyMng = NewObject<ULobbyMng>();
	_pInGameMng = NewObject<UInGameMng>();
	_pDataMng = NewObject<UDataMng>();

	_pUIMng->Init();
	_pLobbyMng->Init();
	_pInGameMng->Init();
	_pDataMng->Init();

	//19.03.05 guhyun 
	//���� ���� ���� ���ϱ� ���� ������ Ű�� �ٷ� InGame���� ����
	if (IS_VALID(_pInGameMng))
	{
		_pInGameMng->Enter();
	}
}

void UMainFramework::UpdateMainFramework(float in_DeltaSeconds)
{
	if (IS_VALID(_pLobbyMng))
	{
		_pLobbyMng->Update(in_DeltaSeconds);
	}

	if (IS_VALID(_pInGameMng))
	{
		_pInGameMng->Update(in_DeltaSeconds);
	}

	if (IS_VALID(_pUIMng))
	{
		_pUIMng->Update(in_DeltaSeconds);
	}

	if (IS_VALID(_pDataMng))
	{
		_pUIMng->Update(in_DeltaSeconds);
	}
}

void UMainFramework::Shutdown()
{
	if (IS_VALID(_pLobbyMng))
	{
		_pLobbyMng->ShutDown();
	}

	if (IS_VALID(_pInGameMng))
	{
		_pInGameMng->ShutDown();
	}

	if (IS_VALID(_pUIMng))
	{
		_pUIMng->ShutDown();
	}

	if (IS_VALID(_pDataMng))
	{
		_pDataMng->ShutDown();
	}

	_pInGameMng = nullptr;
	_pLobbyMng = nullptr;
	_pUIMng = nullptr;
	_pDataMng = nullptr;
}
