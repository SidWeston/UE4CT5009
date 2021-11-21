// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TimelineComponent.h"
#include "InteractionComponent.h"
#include "Lift.generated.h"

UCLASS()
class UE4MECHANICSSANDBOX_API ALift : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALift();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* liftMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* liftTrigger;

	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* liftTimeline;

	FVector liftStartPos;

	UPROPERTY(VisibleAnywhere, meta = (MakeEditWidget = true))
	FVector liftEndPos;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UCurveFloat* liftCurve;

	FOnTimelineFloat UpdateTimelineFloat;

	UFUNCTION()
	void UpdateTimelineComp(float output);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
