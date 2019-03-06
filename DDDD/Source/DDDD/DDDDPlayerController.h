// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DDDDPlayerController.generated.h"

/**
 * 
 */

class ALobbyPawn;
class AInGamePawn;

UCLASS()
class DDDD_API ADDDDPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void					BeginPlay() override;

public:
	void					CreatePawns();
	void					PossessToLobbyPawn();
	void					PossessToInGamePawn();	
private:
	UPROPERTY()
	ALobbyPawn*				_pLobbyPawn;

	UPROPERTY()
	AInGamePawn*			_pInGamePawn;
};
