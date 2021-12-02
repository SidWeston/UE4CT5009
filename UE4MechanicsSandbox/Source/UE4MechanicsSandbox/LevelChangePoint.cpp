// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelChangePoint.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelChangePoint::ALevelChangePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Level Change Base"));
	pointMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	pointTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Level Change Trigger"));
	pointTrigger->AttachToComponent(pointMesh, FAttachmentTransformRules::KeepWorldTransform);
	pointTrigger->OnComponentBeginOverlap.AddDynamic(this, &ALevelChangePoint::OnBoxBeginOverlap);

}

// Called when the game starts or when spawned
void ALevelChangePoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelChangePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelChangePoint::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if(playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())
	{
		UGameplayStatics::OpenLevel(GetWorld(), levelName);
	}
}


