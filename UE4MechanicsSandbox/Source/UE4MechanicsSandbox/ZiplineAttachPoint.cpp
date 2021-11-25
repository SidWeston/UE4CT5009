// Fill out your copyright notice in the Description page of Project Settings.


#include "ZiplineAttachPoint.h"

// Sets default values
AZiplineAttachPoint::AZiplineAttachPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	attachPointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Attach Point"));
	attachPointMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	interactionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction Component"));
	interactionComponent->FInteract.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(AZiplineAttachPoint, OnInteract));

}

// Called when the game starts or when spawned
void AZiplineAttachPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZiplineAttachPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZiplineAttachPoint::OnInteract()
{
	
}