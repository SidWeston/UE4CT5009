// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	doorMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	boxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Door Trigger"));
	boxTrigger->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(boxTrigger->OverlapComponent(boxTrigger->GetComponentLocation(), boxTrigger->GetComponentQuat(), boxTrigger->GetCollisionShape()))
	{
		doorMesh->SetRelativeRotation(targetRotation);
	}

}




