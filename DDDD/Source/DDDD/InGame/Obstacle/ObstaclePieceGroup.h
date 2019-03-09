// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstaclePieceGroup.generated.h"

//��ֹ� �׷��ο� Ŭ����. RootComponent ���� �־�� �θ� ���ͷ� ���ϵ�� ���ϼ��ִٰ���

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
