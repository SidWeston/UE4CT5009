// Fill out your copyright notice in the Description page of Project Settings.


#include "WeightedButtonDoor.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeightedButtonDoor::AWeightedButtonDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	doorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame"));
	doorFrame->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	doorMesh->AttachToComponent(doorFrame, FAttachmentTransformRules::KeepWorldTransform);

	weightedButton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weighted Button"));
	weightedButton->AttachToComponent(doorFrame, FAttachmentTransformRules::KeepWorldTransform);

	buttonTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Button Trigger"));
	buttonTrigger->AttachToComponent(weightedButton, FAttachmentTransformRules::KeepWorldTransform);

	buttonTrigger->OnComponentBeginOverlap.AddDynamic(this, &AWeightedButtonDoor::OnBoxBeginOverlap);
	buttonTrigger->OnComponentEndOverlap.AddDynamic(this, &AWeightedButtonDoor::OnBoxEndOverlap);

	doorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Door Timeline"));

}

// Called when the game starts or when spawned
void AWeightedButtonDoor::BeginPlay()
{
	Super::BeginPlay();

	closedLocation = doorMesh->GetRelativeLocation();

	updateTimelineFloat.BindDynamic(this, &AWeightedButtonDoor::UpdateTimelineComp);

	if (doorCurve)
	{
		doorTimeline->AddInterpFloat(doorCurve, updateTimelineFloat);
	}

}

// Called every frame
void AWeightedButtonDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeightedButtonDoor::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap"));

	if(OtherActor->ActorHasTag("Player"))
	{
		playerOnButton = true;
		doorTimeline->Play();
	}
	else if(OtherActor->ActorHasTag("Pickup"))
	{
		objectOnButton = true;
		doorTimeline->Play();
	}
}

void AWeightedButtonDoor::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor->ActorHasTag("Player"))
	{
		playerOnButton = false;
		if(!objectOnButton)
		{
			doorTimeline->Reverse();
		}
	}
	else if(OtherActor->ActorHasTag("Pickup"))
	{
		objectOnButton = false;
		if(!playerOnButton)
		{
			doorTimeline->Reverse();
		}
	}
}

void AWeightedButtonDoor::UpdateTimelineComp(float output)
{
	doorMesh->SetRelativeLocation(FMath::Lerp(closedLocation, openLocation, output));
}

