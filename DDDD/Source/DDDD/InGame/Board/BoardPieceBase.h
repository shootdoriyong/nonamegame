// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InGameDefine.h"
#include "BoardPieceBase.generated.h"

class UStaticMeshComponent;
class UMaterial;
class UBoard;
UCLASS()
class DDDD_API ABoardPieceBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoardPieceBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;
public:
	void					Init(UBoard* in_pOwner, int32 in_BoardIndex);
	int32					GetBoardIndex();
	float					GetSizeX();
	float					GetSizeY();
	float					GetSizeZ();

	UBoard*					GetOwnerBoard();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	UStaticMeshComponent*	_pBoardPieceSM;

	UPROPERTY()
	UMaterial*				_pMaterial;

	EBOARD_PIECE_STATE_TYPE	GetState();
	void					SetState(EBOARD_PIECE_STATE_TYPE in_eState);
protected:
	float					GetMeshSizeX();
	float					GetMeshSizeY();
	float					GetMeshSizeZ();
	EBOARD_PIECE_STATE_TYPE _eBoardPieceState;
protected:
	//int32					_BoardIndex;
	UBoard*					_pOwnerBoard;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32					_BoardIndex;		//È®ÀÎ¿ë
};
