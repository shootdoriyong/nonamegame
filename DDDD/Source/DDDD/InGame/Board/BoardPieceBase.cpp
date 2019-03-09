// Fill out your copyright notice in the Description page of Project Settings.

#include "BoardPieceBase.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Board.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ABoardPieceBase::ABoardPieceBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_BoardIndex = -1;
	_pMaterial = nullptr;
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

void ABoardPieceBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (_pBoardPieceSM && _pMaterial)
	{
		UMaterialInstanceDynamic* pMID = UMaterialInstanceDynamic::Create(_pMaterial, nullptr);
		_pBoardPieceSM->SetMaterial(0, pMID);
	}
}

void ABoardPieceBase::Init(UBoard* in_pOwner, int32 in_BoardIndex)
{
	_pOwnerBoard = in_pOwner;
	_BoardIndex = in_BoardIndex;
}

int32 ABoardPieceBase::GetBoardIndex()
{
	return _BoardIndex;
}

float ABoardPieceBase::GetSizeX()
{
	return GetMeshSizeX() * GetActorScale3D().X;
}

float ABoardPieceBase::GetSizeY()
{
	return GetMeshSizeY() * GetActorScale3D().Y;
}

float ABoardPieceBase::GetSizeZ()
{
	return GetMeshSizeZ() * GetActorScale3D().Z;
}

float ABoardPieceBase::GetMeshSizeX()
{
	float Size = 0.0f;

	if (_pBoardPieceSM)
	{
		Size = _pBoardPieceSM->GetStaticMesh()->GetBounds().GetBox().GetSize().X;
	}

	return Size;
}

float ABoardPieceBase::GetMeshSizeY()
{
	float Size = 0.0f;

	if (_pBoardPieceSM)
	{
		Size = _pBoardPieceSM->GetStaticMesh()->GetBounds().GetBox().GetSize().Y;
	}

	return Size;
}

float ABoardPieceBase::GetMeshSizeZ()
{
	float Size = 0.0f;

	if (_pBoardPieceSM)
	{
		Size = _pBoardPieceSM->GetStaticMesh()->GetBounds().GetBox().GetSize().Z;
	}

	return Size;
}

UBoard* ABoardPieceBase::GetOwnerBoard()
{
	return _pOwnerBoard;
}