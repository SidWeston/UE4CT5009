// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "InteractButtonComp.h"
#include "Kismet/GameplayStatics.h"
#include "ButtonLift.generated.h"


UCLASS()
class UE4MECHANICSSANDBOX_API AButtonLift : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AButtonLift();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* liftBase;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* liftMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* liftTrigger;

	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* liftTimeline;

	UPROPERTY(VisibleAnywhere)
	FVector liftStartPos;

	UPROPERTY(VisibleAnywhere, meta = (MakeEditWidget = true))
	FVector liftEndPos;

	UPROPERTY(VisibleAnywhere)
	UInteractButtonComp* liftButton;

	bool playerOnLift;
	bool isLiftUp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UCurveFloat* liftCurve;

	FOnTimelineFloat UpdateTimelineFloat;

	FOnTimelineEvent TimelineFinishedEvent;

	UFUNCTION()
	void UpdateTimelineComp(float output);

	UFUNCTION()
	void TimelineFinished();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
