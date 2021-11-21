// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractButton.h"

// Sets default values
AInteractButton::AInteractButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	buttonBackground = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Back Plate"));
	buttonBackground->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	buttonObject = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Object"));
	buttonObject->AttachToComponent(buttonBackground, FAttachmentTransformRules::KeepWorldTransform);

	interactionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction Component"));
	interactionComponent->FInteract.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(AInteractButton, OnButtonPressed));

	buttonPressed = false;

}

// Called when the game starts or when spawned
void AInteractButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractButton::OnButtonPressed()
{
	if(buttonPressed)
	{
		buttonPressed = false;
	}
	else if(!buttonPressed)
	{
		buttonPressed = true;
	}
}
