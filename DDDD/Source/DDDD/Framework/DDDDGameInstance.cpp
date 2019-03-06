// Fill out your copyright notice in the Description page of Project Settings.

#include "DDDDGameInstance.h"
#include "Delegates/IDelegateInstance.h"
#include "DefineMacro.h"
#include "MainFramework.h"
#include "Misc/CoreDelegates.h"

void UDDDDGameInstance::Init()
{
	Super::Init();

	FCoreDelegates::ApplicationWillTerminateDelegate.AddUObject(this, &UDDDDGameInstance::StopTick);
}

void UDDDDGameInstance::StartGame()
{
	UObject* a = GEngine->GameSingleton;
	UMainFramework * MainFramework = Cast <UMainFramework>(GEngine->GameSingleton);

	if (MainFramework)
	{
		MainFramework->Init(this);
	}
	
	_TickDelegate = FTickerDelegate::CreateUObject(this, &UDDDDGameInstance::Tick);
	_TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(_TickDelegate);
}

void UDDDDGameInstance::StartGameInstance()
{
	StartGame();

	Super::StartGameInstance();
	return;


}

#if WITH_EDITOR
FGameInstancePIEResult UDDDDGameInstance::StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params)
{
	StartGame();

	FGameInstancePIEResult Reuslt = Super::StartPlayInEditorGameInstance(LocalPlayer, Params);


	return Reuslt;

}
#endif

bool UDDDDGameInstance::Tick(float DeltaSeconds)
{
	if (IS_VALID(GEngine))
	{
		UMainFramework * MainFramework = Cast <UMainFramework>(GEngine->GameSingleton);

		if (IS_VALID(MainFramework))
		{
			MainFramework->UpdateMainFramework(DeltaSeconds);
		}
	}

	return true;
}

void UDDDDGameInstance::Shutdown()
{
	StopTick();

	if (IS_VALID(GEngine))
	{
		UMainFramework * MainFramework = Cast <UMainFramework>(GEngine->GameSingleton);

		if (IS_VALID(MainFramework))
		{
			MainFramework->Shutdown();

		}
	}

	Super::Shutdown();
}

void UDDDDGameInstance::StopTick()
{
	if (_TickDelegateHandle.IsValid())
	{
		FTicker::GetCoreTicker().RemoveTicker(_TickDelegateHandle);

		_TickDelegateHandle.Reset();
	}
}


