// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "InspectableItem.generated.h"

UCLASS()
class UE4MECHANICSSANDBOX_API AInspectableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInspectableItem();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* itemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString itemName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString itemDescription;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector startPosition;
	FVector targetPositon;
	FRotator startRotation;
	FRotator targetRotation;

	void SetItemTransform(FVector positionToSet, FRotator rotationToSet);

	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* itemTimeline;

	UPROPERTY(EditAnywhere)
	UCurveFloat* itemCurve;

	FOnTimelineFloat updateTimelineFloat;

	UFUNCTION()
	void UpdateTimelineComp(float output);

};
