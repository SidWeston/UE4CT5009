// Fill out your copyright notice in the Description page of Project Settings.


#include "InspectableItem.h"

// Sets default values
AInspectableItem::AInspectableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	itemMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	itemTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Item Timeline"));

}

// Called when the game starts or when spawned
void AInspectableItem::BeginPlay()
{
	Super::BeginPlay();

	startPosition = this->GetActorLocation();

	updateTimelineFloat.BindDynamic(this, &AInspectableItem::UpdateTimelineComp);

	if (itemCurve)
	{
		//add the float track to the timeline
		itemTimeline->AddInterpFloat(itemCurve, updateTimelineFloat);
	}

}

// Called every frame
void AInspectableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AInspectableItem::SetItemTransform(FVector positionToSet, FRotator rotationToSet)
{
	targetPositon = positionToSet;
	targetRotation = rotationToSet;
	itemTimeline->Play();
}


void AInspectableItem::UpdateTimelineComp(float output)
{
	this->SetActorLocationAndRotation(FMath::Lerp(startPosition, targetPositon, output), FMath::Lerp(startRotation, targetRotation, output));
}

