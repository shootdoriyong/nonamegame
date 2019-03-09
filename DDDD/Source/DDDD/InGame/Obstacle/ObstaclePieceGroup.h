// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstaclePieceGroup.generated.h"

//장애물 그루핑용 클래스. RootComponent 세팅 있어야 부모 액터로 차일드로 붙일수있다고함

UCLASS()
class DDDD_API AObstaclePieceGroup: public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AObstaclePieceGroup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
