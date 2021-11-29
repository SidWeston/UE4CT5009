// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"
#include "InteractionComponent.h"
#include "CodeDoorV2.generated.h"

//forward declare
class ADualViewCharacterController;

UCLASS()
class UE4MECHANICSSANDBOX_API ACodeDoorV2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACodeDoorV2();

	//materials showing whether the door is locked or unlocked
	UPROPERTY(EditAnywhere)
	UMaterial* lockedMaterial;
	UPROPERTY(EditAnywhere)
	UMaterial* unlockedMaterial;

	//static mesh components
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* doorFrame;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* doorMesh;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* keypadBack;
	UPROPERTY(VisibleAnywhere)
	UInteractionComponent* interactionComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* keypadCamera;

	//vectors for the closed and open positions of the door mesh
	//open location should be editable within the editor to make it easier to configure
	UPROPERTY(EditAnywhere)
	FVector openLocation;
	FVector closedLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString doorCode; //the code that is required to be entered for the door to open

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool playerInRange; //is the player in range of the door for it to open

	UPROPERTY()
	bool doorUnlocked; //is the door unlocked from the keypad
	bool onKeypad; //if the player is interacting with the keypad
	UPROPERTY(VisibleAnywhere, meta = (MakeEditWidget))
	FVector playerKeypadPosition;

	//box trigger
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* doorTrigger;

	//timeline component
	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* doorTimeline;

	ADualViewCharacterController* playerCharacter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UCurveFloat* doorCurve;

	FOnTimelineFloat updateTimelineFloat;

	UFUNCTION()
	void UpdateTimelineComp(float output);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) //allows the widget component to be referenced as a variable within the blueprint editor
	UWidgetComponent* keyPadWidget;

	UFUNCTION(BlueprintCallable) //allows the function to be called within the blueprint editor
	void CheckCode(FString CodeEntered);

	//overlap functions for the box trigger
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//interact function
	UFUNCTION()
	void OnInteract();

};
