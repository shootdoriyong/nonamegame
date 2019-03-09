// Fill out your copyright notice in the Description page of Project Settings.
#include "ObstaclePieceGroup.h"

// Sets default values
AObstaclePieceGroup::AObstaclePieceGroup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AObstaclePieceGroup::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AObstaclePieceGroup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}