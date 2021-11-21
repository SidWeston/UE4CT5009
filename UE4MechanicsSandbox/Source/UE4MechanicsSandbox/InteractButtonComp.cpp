// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractButtonComp.h"

// Sets default values for this component's properties
UInteractButtonComp::UInteractButtonComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	buttonObject = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	if(GetOwner())
	{
		buttonObject->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}

	interactionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
	interactionComponent->FInteract.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(UInteractButtonComp, OnButtonPressed));

	buttonPressed = false;

	// ...
}


// Called when the game starts
void UInteractButtonComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractButtonComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractButtonComp::OnButtonPressed()
{
	if(!buttonPressed)
	{
		buttonPressed = true;
	}
	else if(buttonPressed)
	{
		buttonPressed = false;
	}
}

