// Fill out your copyright notice in the Description page of Project Settings.


#include "Lift.h"

#include "GameFramework/Character.h"

// Sets default values
ALift::ALift()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	liftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lift Mesh"));
	liftMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	liftTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Lift Trigger"));
	liftTrigger->AttachToComponent(liftMesh, FAttachmentTransformRules::KeepWorldTransform);

	liftTrigger->OnComponentBeginOverlap.AddDynamic(this, &ALift::OnBeginOverlap);
	liftTrigger->OnComponentEndOverlap.AddDynamic(this, &ALift::OnEndOverlap);

	liftTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Lift Timeline"));

}

// Called when the game starts or when spawned
void ALift::BeginPlay()
{
	Super::BeginPlay();

	liftStartPos = GetActorLocation();
	liftEndPos += GetActorLocation();

	UpdateTimelineFloat.BindDynamic(this, &ALift::UpdateTimelineComp);

	if(liftCurve)
	{
		liftTimeline->AddInterpFloat(liftCurve, UpdateTimelineFloat);
	}

}

// Called every frame
void ALift::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALift::UpdateTimelineComp(float output)
{
	liftMesh->SetRelativeLocation(FMath::Lerp(liftStartPos, liftEndPos, output));
}

void ALift::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if(playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())
	{
		liftTimeline->Play();
	}
}

void ALift::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())
	{
		liftTimeline->Reverse();
	}
}

