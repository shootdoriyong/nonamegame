// Fill out your copyright notice in the Description page of Project Settings.

#include "InGamePawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AInGamePawn::AInGamePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create our components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	_pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	_pSpringArm->SetupAttachment(RootComponent);
	_pSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(-90.0f, 0.0f, 0.0f));
	_pSpringArm->TargetArmLength = 0.0f;
	_pSpringArm->bEnableCameraLag = true;
	_pSpringArm->CameraLagSpeed = 3.0f;

	_pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	//_pCamera->SetRelativeRotation(FRotator(-90, 0, 0));
	_pCamera->SetupAttachment(_pSpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void AInGamePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInGamePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AInGamePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("MouseLeftBtn", IE_Pressed, this, &AInGamePawn::MouseLeftPressed);
	PlayerInputComponent->BindAction("MouseLeftBtn", IE_Released, this, &AInGamePawn::MouseLeftReleased);

	PlayerInputComponent->BindAxis("W", this, &AInGamePawn::MoveForward);
	PlayerInputComponent->BindAxis("S", this, &AInGamePawn::MoveBackward);
	PlayerInputComponent->BindAxis("A", this, &AInGamePawn::MoveLeft);
	PlayerInputComponent->BindAxis("D", this, &AInGamePawn::MoveRight);
	PlayerInputComponent->BindAxis("Wheel", this, &AInGamePawn::Zoom);
}

void AInGamePawn::MouseLeftPressed()
{
	UE_LOG(LogClass, Warning, TEXT("MouseLeftPressed"));
}

void AInGamePawn::MouseLeftReleased()
{
	UE_LOG(LogClass, Warning, TEXT("MouseLeftReleased"));
}

void AInGamePawn::MoveForward(float in_AxisValue)
{
	FVector NewLocation = GetActorLocation();
	NewLocation.X += in_AxisValue * 10;
	SetActorLocation(NewLocation);
}

void AInGamePawn::MoveBackward(float in_AxisValue)
{
	FVector NewLocation = GetActorLocation();
	NewLocation.X -= in_AxisValue * 10;
	SetActorLocation(NewLocation);
}

void AInGamePawn::MoveLeft(float in_AxisValue)
{
	FVector NewLocation = GetActorLocation();
	NewLocation.Y -= in_AxisValue * 10;
	SetActorLocation(NewLocation);
}

void AInGamePawn::MoveRight(float in_AxisValue)
{
	FVector NewLocation = GetActorLocation();
	NewLocation.Y += in_AxisValue * 10;
	SetActorLocation(NewLocation);
}

void AInGamePawn::Zoom(float in_AxisValue)
{
	_pSpringArm->TargetArmLength += in_AxisValue * 10;
}