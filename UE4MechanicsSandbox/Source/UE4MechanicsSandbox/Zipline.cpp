// Fill out your copyright notice in the Description page of Project Settings.

#include "kismet/GameplayStatics.h"
#include "Zipline.h"

// Sets default values
AZipline::AZipline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ziplineStart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Zipline Start"));
	ziplineStart->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	ziplineEnd = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Zipline end"));
	ziplineEnd->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	ziplineCable = CreateDefaultSubobject<UCableComponent>(TEXT("Zipline Cable"));
	ziplineCable->AttachToComponent(ziplineStart, FAttachmentTransformRules::KeepWorldTransform);

	const FVector location = ziplineEnd->GetComponentLocation();
	const FRotator rotation(0, 0, 0);
	const FActorSpawnParameters spawnParam;
	ropeAttachPoint = GetWorld()->SpawnActor<ARopeAttachPoint>(location, rotation, spawnParam);
	ziplineCable->SetAttachEndTo(ropeAttachPoint, "None", "None");
	ziplineCable->SetHiddenInGame(false);

	ziplineInteraction = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction Component"));
	ziplineInteraction->FInteract.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(AZipline, OnInteract));

}

// Called when the game starts or when spawned
void AZipline::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZipline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZipline::OnInteract()
{
	const ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}
