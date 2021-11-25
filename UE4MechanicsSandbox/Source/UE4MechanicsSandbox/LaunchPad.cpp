// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPad.h"
#include "DualViewCharacterController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ALaunchPad::ALaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create launch pad mesh
	launchPadBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Launch Pad Base"));
	launchPadBody->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	launchVelocity = 500.0f; //default launch velocity value, can be changed in editor

}

// Called when the game starts or when spawned
void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



