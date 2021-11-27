// Fill out your copyright notice in the Description page of Project Settings.


#include "Zipline.h"
#include "kismet/GameplayStatics.h"
#include "DualViewCharacterController.h"
#include "GameFramework/Character.h"

// Sets default values
AZipline::AZipline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ziplineAnchorPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Zipline Anchor"));
	ziplineAnchorPoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	ziplineStart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Zipline Start"));
	ziplineStart->AttachToComponent(ziplineAnchorPoint, FAttachmentTransformRules::KeepWorldTransform);

	ziplineEnd = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Zipline end"));
	ziplineEnd->AttachToComponent(ziplineAnchorPoint, FAttachmentTransformRules::KeepWorldTransform);

	ziplineCable = CreateDefaultSubobject<UCableComponent>(TEXT("Zipline Cable"));
	ziplineCable->AttachToComponent(ziplineStart, FAttachmentTransformRules::KeepWorldTransform);

	ziplineCable->SetAttachEndToComponent(ziplineEnd, "None");
	ziplineCable->SetHiddenInGame(false);

	ziplineInteraction = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction Component"));
	ziplineInteraction->FInteract.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(AZipline, OnInteract));

	ziplineTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Zipline Timeline"));

}

// Called when the game starts or when spawned
void AZipline::BeginPlay()
{
	Super::BeginPlay();


	updateTimelineFloat.BindDynamic(this, &AZipline::UpdateTimelineComp);

	if (ziplineCurve)
	{
		ziplineTimeline->AddInterpFloat(ziplineCurve, updateTimelineFloat);
	}

	playerCharacter = Cast<ADualViewCharacterController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

}

// Called every frame
void AZipline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(playerCharacter == nullptr) //if the player character is not set, will attempt to find the player character again
	{
		playerCharacter = Cast<ADualViewCharacterController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}

	if(ziplineTimeline->IsPlaying() && playerCharacter->hasJumped)
	{
		ziplineTimeline->Stop();
	}

}

void AZipline::OnInteract()
{

	if(ziplineInteraction->interactedComponent == ziplineStart)
	{
		ziplineTimeline->PlayFromStart();
	}
	else if(ziplineInteraction->interactedComponent == ziplineEnd)
	{
		ziplineTimeline->ReverseFromEnd();
	}

}

void AZipline::UpdateTimelineComp(float output)
{
	playerCharacter->SetActorLocation(FMath::Lerp(ziplineStart->GetComponentLocation(), ziplineEnd->GetComponentLocation(), output));
}

