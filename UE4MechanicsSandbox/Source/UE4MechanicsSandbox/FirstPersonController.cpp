// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonController.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AFirstPersonController::AFirstPersonController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	playerCamera->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	this->GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	moveSpeedMultiplier = 1;

}

// Called when the game starts or when spawned
void AFirstPersonController::BeginPlay()
{
	Super::BeginPlay();

	playerCamera->bUsePawnControlRotation = true;

}

// Called every frame
void AFirstPersonController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFirstPersonController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind input events to call functions
	//Axis mappings are buttons which are held and can have a value between 0 or 1
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AFirstPersonController::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AFirstPersonController::LookUp);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AFirstPersonController::WalkForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AFirstPersonController::WalkRight);
	//action mappings are either on or off and have a value of either 0 or 1
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AFirstPersonController::PlayerJump);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AFirstPersonController::CrouchBegin);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &AFirstPersonController::CrouchEnd);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AFirstPersonController::SprintStart);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AFirstPersonController::SprintEnd);

}

//uses mouseY 
void AFirstPersonController::LookUp(float axisValue)
{
	this->AddControllerPitchInput(axisValue);
}

//uses mouseX
void AFirstPersonController::LookRight(float axisValue)
{
	this->AddControllerYawInput(axisValue);
}

//W + S
void AFirstPersonController::WalkForward(float axisValue)
{
	this->AddMovementInput(this->GetActorForwardVector() * axisValue, moveSpeedMultiplier);
}

//A + D
void AFirstPersonController::WalkRight(float axisValue)
{
	this->AddMovementInput(this->GetActorRightVector() * axisValue, moveSpeedMultiplier);
}

//Spacebar
void AFirstPersonController::PlayerJump()
{
	this->Jump();
}

//Left Control Pressed
void AFirstPersonController::CrouchBegin()
{
	this->Crouch();
}

//Left Control Released
void AFirstPersonController::CrouchEnd()
{
	this->UnCrouch();
}

//left Shift Pressed
void AFirstPersonController::SprintStart()
{
	moveSpeedMultiplier = 2;
}

//Left Shift Released
void AFirstPersonController::SprintEnd()
{
	moveSpeedMultiplier = 1;
}


