// Fill out your copyright notice in the Description page of Project Settings.

#include "BoardPieceBase.h"
#include "Components/BoxComponent.h"

// Sets default values
ABoardPieceBase::ABoardPieceBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_BoardIndex = -1;

	_pBoardPieceSM = CreateDefaultSubobject<UBoxComponent>(TEXT("BoardPiece"));
	
	RootComponent = _pBoardPieceSM;
}

// Called when the game starts or when spawned
void ABoardPieceBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoardPieceBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoardPieceBase::Init(int32 in_BoardIndex)
{
	_BoardIndex = in_BoardIndex;
}

int32 ABoardPieceBase::GetBoardIndex()
{
	return _BoardIndex;
}

