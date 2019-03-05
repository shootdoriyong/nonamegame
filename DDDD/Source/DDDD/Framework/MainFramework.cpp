// Fill out your copyright notice in the Description page of Project Settings.

#include "MainFramework.h"

UMainFramework::UMainFramework(const FObjectInitializer & ObjectInitializer)
{

}

void UMainFramework::Init(UGameInstance* in_GameInstance)
{
	_pMainGameInstance = in_GameInstance;
}

void UMainFramework::UpdateMainFramework(float in_DeltaSeconds)
{

}
void UMainFramework::Shutdown()
{

}


