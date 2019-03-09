// Fill out your copyright notice in the Description page of Project Settings.

#include "ObstaclePieceNormal.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AObstaclePieceNormal::AObstaclePieceNormal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//보드 조각 별 머터리얼이나 메쉬가 다르다면 각각 BP에서 변수로 받아서 BeginPlay에서 세팅 해주자
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> CubeMatAsset(TEXT("Material'/Game/Materials/NormalObstacle.NormalObstacle'"));

	if (CubeMeshAsset.Succeeded())
	{
		_pObstaclePieceSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeVisualComponent"));
		_pObstaclePieceSM->SetStaticMesh(CubeMeshAsset.Object);

		_pMaterial = CubeMatAsset.Object;

		RootComponent = _pObstaclePieceSM;
		SetActorEnableCollision(false);
	}

	_eObstaclePieceState = EOBSTACLE_PIECE_STATE_TYPE::NONE;
}

// Called when the game starts or when spawned
void AObstaclePieceNormal::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AObstaclePieceNormal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

