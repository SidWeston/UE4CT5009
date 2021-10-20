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

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	closedRotation = GetActorRotation(); //sets the closed rotation to the current rotation of the door when the game starts, assumes that the door starts closed

	openRotation = GetActorRotation(); //sets the open rotation to be 90 degrees further on the z axis
	openRotation.Yaw -= 90;

	targetRotation = closedRotation; //sets the target rotation to initially be the closed rotation

	openDoorTimer = 0.0f;

}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (openDoorTimer < 1 && shouldOpen)
	{
		openDoorTimer += DeltaTime;
	}
	else if (openDoorTimer > 1 && shouldOpen)
	{
		openDoorTimer = 1;
	}
	if (!shouldOpen && openDoorTimer > 0)
	{
		openDoorTimer -= DeltaTime;
	}
	else if (!shouldOpen && openDoorTimer < 0)
	{
		openDoorTimer = 0;
	}
		
	doorMesh->SetRelativeRotation(FMath::Lerp(closedRotation, targetRotation, openDoorTimer));
	

}

void ADoor::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult )
{
	const ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())
	{
		targetRotation = openRotation;
		shouldOpen = true;
	}
}

void ADoor::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())
	{
		shouldOpen = false;
	}
}

