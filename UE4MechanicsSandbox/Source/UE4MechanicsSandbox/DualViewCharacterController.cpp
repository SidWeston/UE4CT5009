// Fill out your copyright notice in the Description page of Project Settings.


#include "DualViewCharacterController.h"
#include "InteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ADualViewCharacterController::ADualViewCharacterController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//set initial camera mode
	currentCameraMode = FirstPerson;

	//setup first person camera
	firstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	firstPersonCamera->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	firstPersonCamera->bUsePawnControlRotation = true;

	//setup third person camera
	//third person camera rotates around a spring arm component
	boomArmTP = CreateDefaultSubobject <USpringArmComponent>(TEXT("Boom Arm"));
	boomArmTP->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	boomArmTP->TargetArmLength = 300.0f;
	boomArmTP->bUsePawnControlRotation = true;
	thirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));
	thirdPersonCamera->AttachToComponent(boomArmTP, FAttachmentTransformRules::KeepRelativeTransform);
	thirdPersonCamera->bUsePawnControlRotation = true;
	thirdPersonCamera->SetActive(false);

	//set the rotation rate for the character controller
	GetCharacterMovement()->RotationRate = FRotator(0, 540, 0);
	turnRate = 45;

	walkSpeed = 400;
	sprintSpeed = 1000;
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;

}

// Called when the game starts or when spawned
void ADualViewCharacterController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADualViewCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADualViewCharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind input events to call functions
	//Axis mappings are buttons which are held and can have a value between -1 and 1
	//Mouse Input
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &ADualViewCharacterController::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ADualViewCharacterController::LookUp);
	//WASD Input
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ADualViewCharacterController::WalkForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ADualViewCharacterController::WalkRight);

	//action mappings are either on or off and have a value of either 0 or 1
	//Jump
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ADualViewCharacterController::PlayerJump);
	//Sprint
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &ADualViewCharacterController::SprintStart);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &ADualViewCharacterController::SprintEnd);
	//Player Abilities
	PlayerInputComponent->BindAction(TEXT("AbilityOne"), IE_Pressed, this, &ADualViewCharacterController::UseAbilityOne);
	PlayerInputComponent->BindAction(TEXT("AbilityTwo"), IE_Pressed, this, &ADualViewCharacterController::UseAbilityTwo);
	//Change the player camera
	PlayerInputComponent->BindAction(TEXT("CameraChange"), IE_Pressed, this, &ADualViewCharacterController::ChangeCamera);
	//interact function fires raycast
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &ADualViewCharacterController::DoLineTrace);
}

void ADualViewCharacterController::LookUp(float axisValue)
{
	//change how the controller works based on the current camera mode
	switch (currentCameraMode)
	{
	case FirstPerson:
	{
		this->AddControllerPitchInput(axisValue);
		break;
	}
	case ThirdPerson:
	{
		this->AddControllerPitchInput(axisValue * GetWorld()->GetDeltaSeconds() * turnRate);
		break;
	}
	default:
	{
		break;
	}
	}

}

void ADualViewCharacterController::LookRight(float axisValue)
{
	switch (currentCameraMode)
	{
	case FirstPerson:
	{
		this->AddControllerYawInput(axisValue);
		break;
	}
	case ThirdPerson:
	{
		this->AddControllerYawInput(axisValue * GetWorld()->GetDeltaSeconds() * turnRate);
		break;
	}
	default:
	{
		break;
	}
	}

}

void ADualViewCharacterController::WalkForward(float axisValue)
{
	switch (currentCameraMode)
	{
	case FirstPerson:
	{
		this->AddMovementInput(this->GetActorForwardVector() * axisValue);
		break;
	}
	case ThirdPerson:
	{
		if (Controller != NULL && axisValue != 0)
		{

			const FRotator rotation = Controller->GetControlRotation(); //get the character's rotation
			const FRotator yaw(0, rotation.Yaw, 0); //create a FRotator that only has the yaw value of the controller
			const FVector direction = FRotationMatrix(yaw).GetUnitAxis(EAxis::X); //gets the direction on the x axis(forward)

			AddMovementInput(direction, axisValue); //adds movement in the forward direction
		}

		break;
	}
	default:
	{
		break;
	}
	}
}
void ADualViewCharacterController::WalkRight(float axisValue)
{
	switch (currentCameraMode)
	{
	case FirstPerson:
	{
		this->AddMovementInput(this->GetActorRightVector() * axisValue);
		break;
	}
	case ThirdPerson:
	{
		if (Controller != NULL && axisValue != 0)
		{
			const FRotator rotation = Controller->GetControlRotation();
			const FRotator yaw(0, rotation.Yaw, 0);
			const FVector direction = FRotationMatrix(yaw).GetUnitAxis(EAxis::Y);

			AddMovementInput(direction, axisValue);
		}
		break;
	}
	default:
	{
		break;
	}
	}

}
void ADualViewCharacterController::PlayerJump()
{
	this->Jump();
}
void ADualViewCharacterController::SprintStart()
{
	GetCharacterMovement()->MaxWalkSpeed = sprintSpeed;
}
void ADualViewCharacterController::SprintEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}
void ADualViewCharacterController::UseAbilityOne()
{
	if(JumpMaxCount == 1)
	{
		JumpMaxCount = 2;
	}
	else
	{
		JumpMaxCount = 1;
	}
}
void ADualViewCharacterController::UseAbilityTwo()
{
	
}

void ADualViewCharacterController::ChangeCamera()
{
	if(currentCameraMode == FirstPerson)
	{
		//sets the current camera to be inactive and changes to the other camera
		firstPersonCamera->SetActive(false);
		thirdPersonCamera->SetActive(true);
		//doesnt let the player mesh rotate when the camera is moved
		bUseControllerRotationYaw = false;
		//when the character moves, the mesh will rotate in the direction the player is moving
		GetCharacterMovement()->bOrientRotationToMovement = true;
		//sets the camera mode to be third person
		currentCameraMode = ThirdPerson;
	}
	else if(currentCameraMode == ThirdPerson)
	{
		//sets the current camera to be inactive and changes to the other camera
		thirdPersonCamera->SetActive(false);
		firstPersonCamera->SetActive(true);
		//lets the player mesh be rotated when the camera is moved
		bUseControllerRotationYaw = true;
		//since the mesh is rotated when the camera is moved, doesnt need to be rotated when the character itself is moved
		GetCharacterMovement()->bOrientRotationToMovement = false;
		//sets the camera mode to be first person
		currentCameraMode = FirstPerson;
	}
}

void ADualViewCharacterController::DoLineTrace()
{
	FHitResult outHit;
	//Create start location for the raycast
	FVector startLocation = firstPersonCamera->GetComponentLocation();
	//Create end location
	FVector endLocation = ((firstPersonCamera->GetForwardVector() * 1000.0f) + startLocation);
	//Create collision parameters
	FCollisionQueryParams collisionParams;

	//draw the line in the game for debug purposes
	DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Red, false, 1, 0, 1);

	//Start the line trace
	if(GetWorld()->LineTraceSingleByChannel(outHit, startLocation, endLocation, ECC_Visibility, collisionParams))
	{
		if(outHit.GetActor()->ActorHasTag("Interactable") || outHit.GetComponent()->ComponentHasTag("Interactable"))
		{
			if(outHit.GetActor()->FindComponentByClass<UInteractionComponent>())
			{
				outHit.GetActor()->FindComponentByClass<UInteractionComponent>()->ActivationFunction(); 
			}
		}
	}
}
