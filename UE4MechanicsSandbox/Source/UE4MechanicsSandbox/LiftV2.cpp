// Fill out your copyright notice in the Description page of Project Settings.


#include "LiftV2.h"

#include "GameFramework/Character.h"

// Sets default values
ALiftV2::ALiftV2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	liftBack = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lift Back"));
	liftBack->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	liftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lift Mesh"));
	liftMesh->AttachToComponent(liftBack, FAttachmentTransformRules::KeepWorldTransform);

	liftTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Lift Trigger"));
	liftTrigger->AttachToComponent(liftMesh, FAttachmentTransformRules::KeepWorldTransform);

	liftTrigger->OnComponentBeginOverlap.AddDynamic(this, &ALiftV2::OnBeginOverlap);
	liftTrigger->OnComponentEndOverlap.AddDynamic(this, &ALiftV2::OnEndOverlap);

	liftTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Lift Timeline"));

}

// Called when the game starts or when spawned
void ALiftV2::BeginPlay()
{
	Super::BeginPlay();

	liftStartPos = GetActorLocation();
	liftEndPos += GetActorLocation();

	UpdateTimelineFloat.BindDynamic(this, &ALiftV2::UpdateTimelineComp);
	TimelineFinishedEvent.BindDynamic(this, &ALiftV2::TimelineFinished);

	if (liftCurve)
	{
		liftTimeline->AddInterpFloat(liftCurve, UpdateTimelineFloat);
		liftTimeline->SetTimelineFinishedFunc(TimelineFinishedEvent);
	}

}

// Called every frame
void ALiftV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALiftV2::UpdateTimelineComp(float output)
{
	liftMesh->SetWorldLocation(FMath::Lerp(liftStartPos, liftEndPos, output));
}

void ALiftV2::TimelineFinished()
{
	if(isLiftUp)
	{
		isLiftUp = false;
	}
	else if(!isLiftUp)
	{
		isLiftUp = true;
	}
}

void ALiftV2::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())
	{
		if(isLiftUp)
		{
			liftTimeline->Reverse();
		}
		else if(!isLiftUp)
		{
			liftTimeline->Play();
		}
	}
}

void ALiftV2::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())
	{
		//if(liftTimeline->IsPlaying())
		//{
		//	liftTimeline->Reverse();
		//}
		//else if(liftTimeline->IsReversing())
		//{
		//	liftTimeline->Play();
		//}
	}
}


