// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CableComponent.h"
#include "InteractionComponent.h"
#include "RopeAttachPoint.h"
#include "Zipline.generated.h"

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
	UStaticMeshComponent* ziplineStart;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ziplineEnd;

	UPROPERTY(VisibleAnywhere)
	UInteractionComponent* ziplineInteraction;

	UPROPERTY(VisibleAnywhere)
	ARopeAttachPoint* ropeAttachPoint;

	UPROPERTY(EditAnywhere)
	float travelTime;

	UPROPERTY(VisibleAnywhere, meta = (MakeEditWidget))
	FVector ziplinePointOne;
	UPROPERTY(VisibleAnywhere, meta = (MakeEditWidget))
	FVector ziplinePointTwo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnInteract();


};
