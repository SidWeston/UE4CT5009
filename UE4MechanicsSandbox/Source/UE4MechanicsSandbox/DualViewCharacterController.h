// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DualViewCharacterController.generated.h"

UCLASS()
class UE4MECHANICSSANDBOX_API ADualViewCharacterController : public ACharacter
{
	GENERATED_BODY()

public:
	enum CameraMode
	{
		FirstPerson,
		ThirdPerson
	};

	// Sets default values for this character's properties
	ADualViewCharacterController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	CameraMode currentCameraMode;

	//Input functions
	//Mouse/Camera input
	void LookUp(float axisValue);
	void LookRight(float axisValue);
	//WASD/Movement Input
	void WalkForward(float axisValue);
	void WalkRight(float axisValue);
	//Action Inputs
	//Jump
	void PlayerJump();
	//Sprint
	void SprintStart();
	void SprintEnd();
	//Player Abilities
	void UseAbilityOne();
	void UseAbilityTwo();
	//Change camera mode between first and third person
	void ChangeCamera();

	UPROPERTY(VisibleAnywhere);
	UCameraComponent* firstPersonCamera;

	UPROPERTY(VisibleAnywhere);
	UCameraComponent* thirdPersonCamera;

	UPROPERTY(VisibleAnywhere);
	USpringArmComponent* boomArmTP;

	float turnRate;

	float walkSpeed;
	float sprintSpeed;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
