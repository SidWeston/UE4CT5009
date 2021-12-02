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
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DualViewCharacterController.generated.h"

//forward declare
class AInspectableItem;

UCLASS()
class UE4MECHANICSSANDBOX_API ADualViewCharacterController : public ACharacter
{
	GENERATED_BODY()

public:
	enum CameraMode //enum adds the possibility for more camera/movement modes to be added
	{
		FirstPerson,
		ThirdPerson,
	};

	// Sets default values for this character's properties
	ADualViewCharacterController();

	bool hasJumped, hasDashed;

	CameraMode currentCameraMode;
	UPROPERTY(VisibleAnywhere);
	UCameraComponent* firstPersonCamera;
	UPROPERTY(VisibleAnywhere);
	UCameraComponent* thirdPersonCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	bool isSprinting; //true if the player is currently sprinting
	//values for stamina, max stamina and how fast it drains
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float stamina; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float maxStamina;
	UPROPERTY(EditAnywhere)
	float staminaDrainRate; 

	//item inspection
	UPROPERTY(EditAnywhere)
	USphereComponent* itemInspectLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isInspecting;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AInspectableItem* itemToInspect;

	//pick up/carry objects
	UPhysicsHandleComponent* physicsHandle;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void DoLineTrace();
	void ReleaseWidgetInteraction();
	void FireGrappleHook();
	void ReleaseGrappleHook();

};
