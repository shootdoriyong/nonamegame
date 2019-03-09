// Fill out your copyright notice in the Description page of Project Settings.

#include "BoardPieceNormal.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ABoardPieceNormal::ABoardPieceNormal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//���� ���� �� ���͸����̳� �޽��� �ٸ��ٸ� ���� BP���� ������ �޾Ƽ� BeginPlay���� ���� ������
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> CubeMatAsset(TEXT("Material'/Game/Materials/NormalBoard.NormalBoard'"));

	if (CubeMeshAsset.Succeeded())
	{
		_pBoardPieceSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeVisualComponent"));
		_pBoardPieceSM->SetStaticMesh(CubeMeshAsset.Object);

		_pMaterial = CubeMatAsset.Object;

		RootComponent = _pBoardPieceSM;
		//SetActorEnableCollision(false);
	}
}

// Called when the game starts or when spawned
void ABoardPieceNormal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoardPieceNormal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

