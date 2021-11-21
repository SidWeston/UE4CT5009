// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "InteractDoor.generated.h"

UCLASS()
class UE4MECHANICSSANDBOX_API AInteractDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractDoor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* doorFrame;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* doorMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* doorTrigger;

	UPROPERTY(VisibleAnywhere)
	UInteractionComponent* interactionComponent;

	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* doorTimeline;
	
	bool playerInRange;

	UPROPERTY(EditAnywhere)
	FRotator targetRotation;

	UPROPERTY(VisibleAnywhere)
	FRotator positiveRotation;

	UPROPERTY(VisibleAnywhere)
	FRotator negativeRotation;

	FRotator closedRotation;

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

	UFUNCTION()
	void InteractWithDoor();

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
