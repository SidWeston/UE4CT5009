// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/WidgetInteractionComponent.h"
#include "CableComponent.h"
#include "RopeAttachPoint.h"
#include "DualViewCharacterController.generated.h"

UCLASS()
class UE4MECHANICSSANDBOX_API ADualViewCharacterController : public ACharacter
{
	GENERATED_BODY()

public:
	enum CameraMode
	{
		FirstPerson,
		ThirdPerson,
	};

	// Sets default values for this character's properties
	ADualViewCharacterController();

	bool hasJumped, hasDashed;

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

	UPROPERTY(EditAnywhere)
	float jumpHeight;
	UPROPERTY(EditAnywhere)
	float dashLength;

	float walkSpeed, sprintSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetInteractionComponent* widgetInteraction;

	//grapple hook
	UPROPERTY(VisibleAnywhere)
	UCableComponent* grappleHook;
	bool hookAttached;
	FVector swingPoint;
	UPROPERTY(EditAnywhere)
	float maxSwingSpeed;
	UPROPERTY(VisibleAnywhere)
	ARopeAttachPoint* ropeAttachPoint; //empty actor used to attach the end of the grapple hook to where the raycast lands

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void DoLineTrace();
	void FireGrappleHook();
	void ReleaseGrappleHook();

};
