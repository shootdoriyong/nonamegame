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

	//���� ���� �� ���͸����̳� �޽��� �ٸ��ٸ� ���� BP���� ������ �޾Ƽ� BeginPlay���� ���� ������
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

