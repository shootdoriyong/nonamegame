// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InGamePawn.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class DDDD_API AInGamePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AInGamePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere)
	USpringArmComponent*			_pSpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent*				_pCamera;

public:
	void							MoveForward(float in_AxisValue);
	void							MoveBackward(float in_AxisValue);
	void							MoveLeft(float in_AxisValue);
	void							MoveRight(float in_AxisValue);
	void							Zoom(float in_AxisValue);
	void							MouseLeftPressed();
	void							MouseLeftReleased();
};
