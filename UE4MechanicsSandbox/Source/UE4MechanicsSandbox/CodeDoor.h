// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Components/TimelineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CodeDoor.generated.h"


UCLASS()
class UE4MECHANICSSANDBOX_API ACodeDoor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ACodeDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* doorFrame;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* doorMesh;

	UPROPERTY(EditAnywhere)
	FVector openLocation;

	FVector closedLocation;

	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* doorTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString doorCode; //the code that is required to be entered for the door to open

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool shouldOpen;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UWidgetComponent* keyPadWidget;

	UPROPERTY(EditAnywhere)
	UCurveFloat* doorCurve;

	FOnTimelineFloat UpdateTimelineFloat;

	UFUNCTION()
	void UpdateTimelineComp(float output);

	UFUNCTION(BlueprintCallable)
	void CheckCode(FString CodeEntered, UUserWidget* UIKeyPad);



};
