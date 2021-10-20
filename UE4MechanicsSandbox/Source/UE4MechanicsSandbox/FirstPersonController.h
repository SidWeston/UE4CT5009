// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "FirstPersonController.generated.h"

UCLASS()
class UE4MECHANICSSANDBOX_API AFirstPersonController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstPersonController();

	//Input functions
	void LookUp(float axisValue);
	void LookRight(float axisValue);
	void WalkForward(float axisValue);
	void WalkRight(float axisValue);
	void PlayerJump();
	void CrouchBegin();
	void CrouchEnd();
	void SprintStart();
	void SprintEnd();

	//create a camera 
	UPROPERTY(EditAnywhere);
	UCameraComponent* playerCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	float moveSpeedMultiplier;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
