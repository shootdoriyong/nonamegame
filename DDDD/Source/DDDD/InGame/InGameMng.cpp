// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMng.h"

void UInGameMng::Init()
{

}

void UInGameMng::Update(float in_DeltaTime)
{

}

void UInGameMng::ShutDown()
{

}

void UInGameMng::Enter()
{
	//���⼭ ���ӿ� �ʿ��� �͵� �ε� ���� ���� ���� ������

	UE_LOG(LogClass, Warning, TEXT("Enter in InGameMng Class"));

	StartGame();
}

void UInGameMng::StartGame()
{
	UE_LOG(LogClass, Warning, TEXT("StartGame in InGameMng Class"));
}