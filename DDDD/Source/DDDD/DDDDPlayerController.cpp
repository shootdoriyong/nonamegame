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
	//Pawn���� ������鰡.. (��ġ) //��ġ�� �߿��� ���� InGamePawn ���� �ε�. Lobby�� �׳� UI�� �״ϱ�
	//InGame ���� �� ���带 ZeroVector �������� �����ϴϱ� ������ ��ġ�� InGamePawn ��ġ�� ���� �س���. �ʿ信 ���� ���� ����

	//LobbyPawn ����
	{
		UClass* pClass = nullptr;
		FString strBPPath = "/Game/BP_LobbyPawn.BP_LobbyPawn_C";

		pClass = Cast<UClass>(StaticLoadClass(ALobbyPawn::StaticClass(), NULL, *strBPPath));

		if (pClass != nullptr)
		{
			_pLobbyPawn = Cast<ALobbyPawn>(GET_MAINFRAMEWORK()->GetGameInstance()->GetWorld()->SpawnActor(pClass));
		}
	}

	//InGamePawn ����
	{
		UClass* pClass = nullptr;
		FString strBPPath = "/Game/BP_InGamePawn.BP_InGamePawn_C";

		pClass = Cast<UClass>(StaticLoadClass(AInGamePawn::StaticClass(), NULL, *strBPPath));

		if (pClass != nullptr)
		{
			//���忡�� ���̰��� ������
			FVector Location = FVector(0, 0, 2000);
			FRotator Rotation = FRotator(0, 0, 0);

			_pInGamePawn = Cast<AInGamePawn>(GET_MAINFRAMEWORK()->GetGameInstance()->GetWorld()->SpawnActor(pClass, &Location, &Rotation));
		}
	}

	PossessToLobbyPawn();

	//���� �ΰ��� ���� �������� �Űܾ���
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