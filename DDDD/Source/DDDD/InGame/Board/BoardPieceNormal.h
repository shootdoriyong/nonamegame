// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoardPieceBase.h"
#include "BoardPieceNormal.generated.h"

UCLASS()
class DDDD_API ABoardPieceNormal : public ABoardPieceBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoardPieceNormal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
