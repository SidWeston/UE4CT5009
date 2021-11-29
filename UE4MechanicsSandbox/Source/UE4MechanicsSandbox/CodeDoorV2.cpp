// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeDoorV2.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "DualViewCharacterController.h"


ACodeDoorV2::ACodeDoorV2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create mesh components
	doorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame"));
	doorFrame->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	doorMesh->AttachToComponent(doorFrame, FAttachmentTransformRules::KeepRelativeTransform);

	keypadBack = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Keypad Back"));
	keypadBack->AttachToComponent(doorFrame, FAttachmentTransformRules::KeepWorldTransform);

	//Create camera to view the keypad
	keypadCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Keypad Camera"));
	keypadCamera->AttachToComponent(doorFrame, FAttachmentTransformRules::KeepWorldTransform);
	keypadCamera->SetActive(false);

	//create widget component
	keyPadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Key Pad"));
	keyPadWidget->AttachToComponent(doorFrame, FAttachmentTransformRules::KeepRelativeTransform);

	//create door trigger component
	doorTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Door Trigger"));
	doorTrigger->AttachToComponent(doorFrame, FAttachmentTransformRules::KeepRelativeTransform);

	//bind overlap functions to door trigger
	doorTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACodeDoorV2::OnBoxBeginOverlap);
	doorTrigger->OnComponentEndOverlap.AddDynamic(this, &ACodeDoorV2::OnBoxEndOverlap);

	//create interaction component
	interactionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("Door Interaction"));
	interactionComponent->FInteract.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ACodeDoorV2, OnInteract));

	doorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Door Timeline"));

	doorUnlocked = false;

}

// Called when the game starts or when spawned
void ACodeDoorV2::BeginPlay()
{
	Super::BeginPlay();
	//set the closed location to be the current location of the door at game start
	closedLocation = doorMesh->GetRelativeLocation();
	//set the keypad material to be locked initially
	keypadBack->SetMaterial(0, lockedMaterial);

	//bind timeline to function
	updateTimelineFloat.BindDynamic(this, &ACodeDoorV2::UpdateTimelineComp);

	if (doorCurve)
	{
		//add the float track to the timeline
		doorTimeline->AddInterpFloat(doorCurve, updateTimelineFloat);
	}

	playerCharacter = Cast<ADualViewCharacterController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

}

// Called every frame
void ACodeDoorV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(playerCharacter == nullptr)
	{
		playerCharacter = Cast<ADualViewCharacterController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}

	if (playerInRange && doorUnlocked) //if the player is within the proximity of the door and the door is unlocked
	{
		doorTimeline->Play();
	}
	else if (!playerInRange || !doorUnlocked) //if either condition is false, it will close the door
	{
		doorTimeline->Reverse();
	}

	if(onKeypad)
	{
		APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		FHitResult outHit;
		playerController->GetHitResultUnderCursorByChannel(TraceTypeQuery1, false, outHit);
		FRotator lookAtMouseRotation = UKismetMathLibrary::FindLookAtRotation(playerCharacter->GetActorLocation(), outHit.Location);
		playerCharacter->firstPersonCamera->SetWorldRotation(lookAtMouseRotation);
	}

}

void ACodeDoorV2::UpdateTimelineComp(float output)
{
	doorMesh->SetRelativeLocation(FMath::Lerp(closedLocation, openLocation, output));
}


void ACodeDoorV2::CheckCode(FString CodeEntered)
{
	if (CodeEntered == doorCode) //if the code is correct
	{
		doorUnlocked = true; //unlocks the door
		keypadBack->SetMaterial(0, unlockedMaterial); //set the material of the door to signify the door is unlocked
	}
	else if (CodeEntered != doorCode) //if the code is incorrect
	{
		doorUnlocked = false; //locks the door
		keypadBack->SetMaterial(0, lockedMaterial); //sets the material to be locked
	}
}

void ACodeDoorV2::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetUniqueID() == playerCharacter->GetUniqueID()) //if the object overlapping with the trigger is the same as the player character
	{
		playerInRange = true; //allows the door to be opened
	}
}

void ACodeDoorV2::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetUniqueID() == playerCharacter->GetUniqueID()) //checks if it matches the overlapping actor
	{
		playerInRange = false; //stops the door from being opened
	}
}

void ACodeDoorV2::OnInteract()
{
	onKeypad = true;
	playerCharacter->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(playerCharacter->GetActorLocation(), keyPadWidget->GetComponentLocation()));
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerCharacter->currentCameraMode == ADualViewCharacterController::ThirdPerson)
	{
		playerCharacter->thirdPersonCamera->SetActive(false);
	}
	else if (playerCharacter->currentCameraMode == ADualViewCharacterController::FirstPerson)
	{
		playerController->SetViewTargetWithBlend(this, 2, VTBlend_Linear, 0, false);
		playerController->bShowMouseCursor = true;
		playerController->bEnableClickEvents = true;
		playerController->bEnableMouseOverEvents = true;
	}
	keypadCamera->SetActive(true);
}
