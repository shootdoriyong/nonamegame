// Fill out your copyright notice in the Description page of Project Settings.

#include "BoardPieceBase.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ABoardPieceBase::ABoardPieceBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_BoardIndex = -1;
	_pMaterial = nullptr;

	//보드 조각 별 머터리얼이나 메쉬가 다르다면 각각 BP에서 변수로 받아서 BeginPlay에서 세팅 해주자
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> CubeMatAsset(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	if (CubeMeshAsset.Succeeded())
	{
		PrimaryActorTick.bCanEverTick = true;
		_pBoardPieceSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeVisualComponent"));
		_pBoardPieceSM->SetStaticMesh(CubeMeshAsset.Object);

		_pMaterial = CubeMatAsset.Object;
		
		RootComponent = _pBoardPieceSM;
		SetActorEnableCollision(false);
	}
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

void ABoardPieceBase::Init(int32 in_BoardIndex)
{
	_BoardIndex = in_BoardIndex;
}

int32 ABoardPieceBase::GetBoardIndex()
{
	return _BoardIndex;
}

