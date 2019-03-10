// Fill out your copyright notice in the Description page of Project Settings.

#include "ObstaclePieceBase.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AObstaclePieceBase::AObstaclePieceBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_pMaterial = nullptr;
}

// Called when the game starts or when spawned
void AObstaclePieceBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AObstaclePieceBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstaclePieceBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (_pObstaclePieceSM && _pMaterial)
	{
		UMaterialInstanceDynamic* pMID = UMaterialInstanceDynamic::Create(_pMaterial, nullptr);
		_pObstaclePieceSM->SetMaterial(0, pMID);
	}
}

void AObstaclePieceBase::Init(int32 in_ObstaclePieceIndex)
{
	_ObstaclePieceIndex = in_ObstaclePieceIndex;
}

float AObstaclePieceBase::GetSizeX()
{
	return GetMeshSizeX() * GetActorScale3D().X;
}

float AObstaclePieceBase::GetSizeY()
{
	return GetMeshSizeY() * GetActorScale3D().Y;
}

float AObstaclePieceBase::GetSizeZ()
{
	return GetMeshSizeZ() * GetActorScale3D().Z;
}

float AObstaclePieceBase::GetMeshSizeX()
{
	float Size = 0.0f;

	if (_pObstaclePieceSM)
	{
		Size = _pObstaclePieceSM->GetStaticMesh()->GetBounds().GetBox().GetSize().X;
	}

	return Size;
}

float AObstaclePieceBase::GetMeshSizeY()
{
	float Size = 0.0f;

	if (_pObstaclePieceSM)
	{
		Size = _pObstaclePieceSM->GetStaticMesh()->GetBounds().GetBox().GetSize().Y;
	}

	return Size;
}

float AObstaclePieceBase::GetMeshSizeZ()
{
	float Size = 0.0f;

	if (_pObstaclePieceSM)
	{
		Size = _pObstaclePieceSM->GetStaticMesh()->GetBounds().GetBox().GetSize().Z;
	}

	return Size;
}

int32 AObstaclePieceBase::GetObstaclePieceIndex()
{
	return _ObstaclePieceIndex;
}

void AObstaclePieceBase::SetState(EOBSTACLE_PIECE_STATE_TYPE in_eObstaclePieceState)
{
	//if (_eObstaclePieceState != in_eObstaclePieceState)
	{
		_eObstaclePieceState = in_eObstaclePieceState;

		SetMaterialByState(_eObstaclePieceState);
	}
}

EOBSTACLE_PIECE_STATE_TYPE AObstaclePieceBase::GetState()
{
	return _eObstaclePieceState;
}

void AObstaclePieceBase::SetMaterialByState(EOBSTACLE_PIECE_STATE_TYPE in_eObstaclePieceState)
{
	if (_eObstaclePieceState == EOBSTACLE_PIECE_STATE_TYPE::HIDDEN)
	{
		if(bHidden == false)
			SetActorHiddenInGame(true);
	}
	else
	{
		if (bHidden == true)
			SetActorHiddenInGame(false);

		if (_eObstaclePieceState == EOBSTACLE_PIECE_STATE_TYPE::PREVIEW)
		{
			if (_pObstaclePieceSM )
			{
				UMaterialInstanceDynamic* pMID = UMaterialInstanceDynamic::Create(_pMaterial, nullptr);
				pMID->SetScalarParameterValue(FName(TEXT("Alpha")), 0.8f);
				//pMID->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor::Gray);
				_pObstaclePieceSM->SetMaterial(0, pMID);
			}
		}
		else if (_eObstaclePieceState == EOBSTACLE_PIECE_STATE_TYPE::PREVIEW_FAIL)
		{
			if (_pObstaclePieceSM)
			{
				UMaterialInstanceDynamic* pMID = UMaterialInstanceDynamic::Create(_pMaterial, nullptr);
				pMID->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor::Red);
				pMID->SetScalarParameterValue(FName(TEXT("Alpha")), 0.8f);
				_pObstaclePieceSM->SetMaterial(0, pMID);
			}
		}
		else if (_eObstaclePieceState == EOBSTACLE_PIECE_STATE_TYPE::ARRANGEMENT)
		{
			if (_pObstaclePieceSM)
			{
				UMaterialInstanceDynamic* pMID = UMaterialInstanceDynamic::Create(_pMaterial, nullptr);
				pMID->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor::White);
				pMID->SetScalarParameterValue(FName(TEXT("Alpha")), 1.0f);
				_pObstaclePieceSM->SetMaterial(0, pMID);
			}
		}
	}
}