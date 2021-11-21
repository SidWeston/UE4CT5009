// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractDoor.h"

#include "GameFramework/Character.h"

// Sets default values
AInteractDoor::AInteractDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	doorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame"));
	doorFrame->SetupAttachment(GetRootComponent());

	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	doorMesh->SetupAttachment(doorFrame);

	doorTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Door Trigger"));
	doorTrigger->SetupAttachment(doorFrame);
	doorTrigger->OnComponentBeginOverlap.AddDynamic(this, &AInteractDoor::OnBoxBeginOverlap);
	doorTrigger->OnComponentEndOverlap.AddDynamic(this, &AInteractDoor::OnBoxEndOverlap);

	doorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Door Timeline"));

	interactionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction Component"));
	interactionComponent->FInteract.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(AInteractDoor, InteractWithDoor));

	positiveRotation = FRotator(0, 90, 0);
	negativeRotation = FRotator(0, -90, 0);

}

// Called when the game starts or when spawned
void AInteractDoor::BeginPlay()
{
	Super::BeginPlay();

	closedRotation = doorMesh->GetRelativeRotation();

	updateTimelineFloat.BindDynamic(this, &AInteractDoor::AInteractDoor::UpdateTimelineComp);

	if(doorCurve)
	{
		doorTimeline->AddInterpFloat(doorCurve, updateTimelineFloat);
	}

}

// Called every frame
void AInteractDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!playerInRange && doorMesh->GetRelativeRotation() != closedRotation) //the player has walked away from the door and the door is open
	{
		doorTimeline->Reverse(); //close the door
	}

}

void AInteractDoor::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if(playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())
	{
		//use dot product to find out which side of the door the player is on
		float isFacing = FVector::DotProduct(playerCharacter->GetActorForwardVector(), this->GetActorForwardVector());
		if (isFacing >= 0)
		{
			targetRotation = positiveRotation;
		}
		else if (isFacing < 0)
		{
			targetRotation = negativeRotation;
		}
		playerInRange = true;
	}
}

void AInteractDoor::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if(playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())
	{
		playerInRange = false;
	}
}

void AInteractDoor::InteractWithDoor()
{
	if(playerInRange)
	{
		if(doorMesh->GetRelativeRotation() == closedRotation) //if the door is closed
		{
			doorTimeline->Play(); //play the timeline forwards
		}
		else if(doorMesh->GetRelativeRotation() == positiveRotation || doorMesh->GetRelativeRotation() == negativeRotation) //if the door is open
		{
			doorTimeline->Reverse(); //play the timeline backwards
		}
	}
}

void AInteractDoor::UpdateTimelineComp(float output)
{
	doorMesh->SetRelativeRotation(FMath::Lerp(this->GetActorRotation(), targetRotation, output));
}