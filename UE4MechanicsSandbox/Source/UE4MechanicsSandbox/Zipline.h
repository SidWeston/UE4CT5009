// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CableComponent.h"
#include "InteractionComponent.h"
#include "Components/TimelineComponent.h"
#include "Zipline.generated.h"

//forward declare
class ADualViewCharacterController;

UCLASS()
class UE4MECHANICSSANDBOX_API AZipline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZipline();

	UPROPERTY(VisibleAnywhere)
	UCableComponent* ziplineCable;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ziplineAnchorPoint;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ziplineStart;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ziplineEnd;

	UPROPERTY(VisibleAnywhere)
	UInteractionComponent* ziplineInteraction;

	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* ziplineTimeline;

	//ACharacter* playerCharacter;
	ADualViewCharacterController* playerCharacter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UCurveFloat* ziplineCurve;

	FOnTimelineFloat updateTimelineFloat;

	UFUNCTION()
	void UpdateTimelineComp(float output);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnInteract();

};
