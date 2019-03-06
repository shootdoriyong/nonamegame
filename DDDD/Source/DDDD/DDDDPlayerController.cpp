// Fill out your copyright notice in the Description page of Project Settings.

#include "DDDDPlayerController.h"
#include "InGamePawn.h"
#include "LobbyPawn.h"
#include "DefineMacro.h"
#include "InGameMng.h"

void ADDDDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	
	CreatePawns();
}

void ADDDDPlayerController::CreatePawns()
{
	//Pawn들을 어따만들가.. (위치) //위치가 중요한 폰은 InGamePawn 정도 인듯. Lobby도 그냥 UI일 테니까
	//InGame 에서 내 보드를 ZeroVector 기준으로 생성하니까 임의의 위치로 InGamePawn 위치를 고정 해놓자. 필요에 따라 추후 변경

	//LobbyPawn 생성
	{
		UClass* pClass = nullptr;
		FString strBPPath = "/Game/BP_LobbyPawn.BP_LobbyPawn_C";

		pClass = Cast<UClass>(StaticLoadClass(ALobbyPawn::StaticClass(), NULL, *strBPPath));

		if (pClass != nullptr)
		{
			_pLobbyPawn = Cast<ALobbyPawn>(GET_MAINFRAMEWORK()->GetGameInstance()->GetWorld()->SpawnActor(pClass));
		}
	}

	//InGamePawn 생성
	{
		UClass* pClass = nullptr;
		FString strBPPath = "/Game/BP_InGamePawn.BP_InGamePawn_C";

		pClass = Cast<UClass>(StaticLoadClass(AInGamePawn::StaticClass(), NULL, *strBPPath));

		if (pClass != nullptr)
		{
			//보드에서 높이값만 높여서
			FVector Location = FVector(0, 0, 2000);
			FRotator Rotation = FRotator(0, 0, 0);

			_pInGamePawn = Cast<AInGamePawn>(GET_MAINFRAMEWORK()->GetGameInstance()->GetWorld()->SpawnActor(pClass, &Location, &Rotation));
		}
	}

	PossessToLobbyPawn();

	//추후 인게임 입장 구문으로 옮겨야함
	GET_INGAME_MANAGER()->Enter();
}

void ADDDDPlayerController::PossessToLobbyPawn()
{
	if(IS_VALID(_pLobbyPawn))
	{
		Possess(_pLobbyPawn);
	}
}

void ADDDDPlayerController::PossessToInGamePawn()
{
	if (IS_VALID(_pInGamePawn))
	{
		Possess(_pInGamePawn);
	}
}