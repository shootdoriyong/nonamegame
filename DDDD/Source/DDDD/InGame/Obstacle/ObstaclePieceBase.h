// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InGameDefine.h"
#include "ObstaclePieceBase.generated.h"

class UStaticMeshComponent;
class UMaterial;

UCLASS()
class DDDD_API AObstaclePieceBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AObstaclePieceBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

public:
	void					Init(int32 in_ObstaclePieceIndex);

	float					GetSizeX();
	float					GetSizeY();
	float					GetSizeZ();

	int32					GetObstaclePieceIndex();

	void					SetState(EOBSTACLE_PIECE_STATE_TYPE in_eObstaclePieceState);
	EOBSTACLE_PIECE_STATE_TYPE	GetState();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
	UStaticMeshComponent*	_pObstaclePieceSM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
	UMaterial*				_pPreviewMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
	UMaterial*				_pMaterial;

protected:
	float					GetMeshSizeX();
	float					GetMeshSizeY();
	float					GetMeshSizeZ();

	void					SetMaterialByState(EOBSTACLE_PIECE_STATE_TYPE in_eObstaclePieceState);


protected:
	//int32					_ObstaclePieceIndex;
	EOBSTACLE_PIECE_STATE_TYPE	_eObstaclePieceState;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32					_ObstaclePieceIndex;		//È®ÀÎ¿ë
};
