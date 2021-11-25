// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonLift.h"

#include "GameFramework/Character.h"

// Sets default values
AButtonLift::AButtonLift()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	liftBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lift Base"));
	liftBase->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	liftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lift Mesh"));
	liftMesh->AttachToComponent(liftBase, FAttachmentTransformRules::KeepWorldTransform);

	liftTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Lift Trigger"));
	liftTrigger->AttachToComponent(liftMesh, FAttachmentTransformRules::KeepWorldTransform);

	liftTrigger->OnComponentBeginOverlap.AddDynamic(this, &AButtonLift::OnBeginOverlap);
	liftTrigger->OnComponentEndOverlap.AddDynamic(this, &AButtonLift::OnEndOverlap);

	liftButton = CreateDefaultSubobject<UInteractButtonComp>(TEXT("Lift Button"));
	liftButton->buttonObject->AttachToComponent(liftMesh, FAttachmentTransformRules::KeepWorldTransform);

	liftTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Lift Timeline"));

	isLiftUp = false;
}

// Called when the game starts or when spawned
void AButtonLift::BeginPlay()
{
	Super::BeginPlay();

	liftStartPos = GetActorLocation();
	liftEndPos += GetActorLocation();

	UpdateTimelineFloat.BindDynamic(this, &AButtonLift::UpdateTimelineComp);
	TimelineFinishedEvent.BindDynamic(this, &AButtonLift::TimelineFinished);

	if (liftCurve)
	{
		liftTimeline->AddInterpFloat(liftCurve, UpdateTimelineFloat);
		liftTimeline->SetTimelineFinishedFunc(TimelineFinishedEvent);
	}

}

// Called every frame
void AButtonLift::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(liftButton->buttonPressed && playerOnLift && !isLiftUp)
	{
		liftTimeline->Play();
	}
	else if(!liftButton->buttonPressed && playerOnLift && isLiftUp)
	{
		liftTimeline->Reverse();
	}

}

void AButtonLift::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if(playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())
	{
		playerOnLift = true;
	}
}

void AButtonLift::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())
	{
		playerOnLift = false;
	}
}

void AButtonLift::UpdateTimelineComp(float output)
{
	liftMesh->SetWorldLocation(FMath::Lerp(liftStartPos, liftEndPos, output));
}

void AButtonLift::TimelineFinished()
{
	if(liftMesh->GetComponentLocation() == liftStartPos)
	{
		isLiftUp = false;
	}
	else if(liftMesh->GetComponentLocation() == liftEndPos)
	{
		isLiftUp = true;
	}
}




