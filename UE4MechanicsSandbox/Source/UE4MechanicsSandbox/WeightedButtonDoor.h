// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "WeightedButtonDoor.generated.h"

UCLASS()
class UE4MECHANICSSANDBOX_API AWeightedButtonDoor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AWeightedButtonDoor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* doorFrame;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* doorMesh;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* weightedButton;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* buttonTrigger;

	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* doorTimeline;

	bool playerOnButton;
	bool objectOnButton;
	UPROPERTY(VisibleAnywhere)
	FVector closedLocation;
	UPROPERTY(EditAnywhere)
	FVector openLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UCurveFloat* doorCurve;

	FOnTimelineFloat updateTimelineFloat;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void UpdateTimelineComp(float output);

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
