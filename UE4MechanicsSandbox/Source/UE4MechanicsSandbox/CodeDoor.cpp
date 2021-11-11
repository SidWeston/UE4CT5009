// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeDoor.h"

// Sets default values
ACodeDoor::ACodeDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	doorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame"));
	doorFrame->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	doorMesh->AttachToComponent(doorFrame, FAttachmentTransformRules::KeepRelativeTransform);

	keyPadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Key Pad"));
	keyPadWidget->AttachToComponent(doorFrame, FAttachmentTransformRules::KeepRelativeTransform);

	doorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Door Timeline"));

}

// Called when the game starts or when spawned
void ACodeDoor::BeginPlay()
{
	Super::BeginPlay();

	closedLocation = doorMesh->GetRelativeLocation();

	UpdateTimelineFloat.BindDynamic(this, &ACodeDoor::UpdateTimelineComp);

	if (doorCurve)
	{
		doorTimeline->AddInterpFloat(doorCurve, UpdateTimelineFloat);
	}

}

// Called every frame
void ACodeDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ACodeDoor::CheckCode(FString CodeEntered, UUserWidget* UIKeyPad)
{
	if (CodeEntered == doorCode)
	{
		doorTimeline->Play();
	}
}

void ACodeDoor::UpdateTimelineComp(float output)
{
	doorMesh->SetRelativeLocation(FMath::Lerp(closedLocation, openLocation, output));
}


