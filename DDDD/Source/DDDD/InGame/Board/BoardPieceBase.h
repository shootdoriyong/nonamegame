// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardPieceBase.generated.h"

class UStaticMeshComponent;
class UMaterial;

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
	void					Init(int32 in_BoardIndex);
	int32					GetBoardIndex();

	float					GetMeshSizeX();
	float					GetMeshSizeY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	UStaticMeshComponent*	_pBoardPieceSM;

	UPROPERTY()
	UMaterial*				_pMaterial;
private:
	int32					_BoardIndex;


};
