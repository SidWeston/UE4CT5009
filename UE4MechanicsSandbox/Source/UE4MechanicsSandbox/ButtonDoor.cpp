// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonDoor.h"

// Sets default values
AButtonDoor::AButtonDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	doorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame"));
	doorFrame->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	doorMesh->AttachToComponent(doorFrame, FAttachmentTransformRules::KeepWorldTransform);

	doorButton = CreateDefaultSubobject<UInteractButtonComp>(TEXT("Door Button"));

	doorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Door Timeline"));

}

// Called when the game starts or when spawned
void AButtonDoor::BeginPlay()
{
	Super::BeginPlay();

	closedLocation = doorMesh->GetRelativeLocation();

	updateTimelineFloat.BindDynamic(this, &AButtonDoor::UpdateTimelineComp);

	if (doorCurve)
	{
		doorTimeline->AddInterpFloat(doorCurve, updateTimelineFloat);
	}


}

// Called every frame
void AButtonDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if the button is turned on and the door is in the closed location
	if(doorButton->buttonPressed && doorMesh->GetRelativeLocation() == closedLocation) 
	{
		doorTimeline->Play(); //opens the door
	}
	else if(!doorButton->buttonPressed && doorMesh->GetRelativeLocation() == openLocation) //if the button is turned off and the door is open
	{
		doorTimeline->Reverse(); //closes the door
	}

}

void AButtonDoor::UpdateTimelineComp(float output)
{
	//set the location of the door based on the output of the timeline
	doorMesh->SetRelativeLocation(FMath::Lerp(closedLocation, openLocation, output));
}

