// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "GameFramework/Character.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	doorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame"));
	doorFrame->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	doorMesh->AttachToComponent(doorFrame, FAttachmentTransformRules::KeepWorldTransform);

	boxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Door Trigger"));
	boxTrigger->AttachToComponent(doorFrame, FAttachmentTransformRules::KeepWorldTransform);

	boxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnBoxBeginOverlap);
	boxTrigger->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnBoxEndOverlap);

	doorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Door Timeline"));

	positiveRotation = FRotator(0, -90, 0);
	negativeRotation = FRotator(0, 90, 0);

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	UpdateTimelineFloat.BindDynamic(this, &ADoor::UpdateTimelineComp);

	if(doorCurve)
	{
		doorTimeline->AddInterpFloat(doorCurve, UpdateTimelineFloat);
	}

}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADoor::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult )
{
	const ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())
	{
		float isFacing = FVector::DotProduct(playerCharacter->GetActorForwardVector(), this->GetActorForwardVector());
		if(isFacing >= 0)
		{
			targetRotation = negativeRotation;
		}
		else if(isFacing < 0)
		{
			targetRotation = positiveRotation;
		}
		doorTimeline->Play();
	}
}

void ADoor::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())
	{
		doorTimeline->Reverse();
	}
}

void ADoor::UpdateTimelineComp(float output)
{
	doorMesh->SetRelativeRotation(FMath::Lerp(this->GetActorRotation(), targetRotation, output));
}



