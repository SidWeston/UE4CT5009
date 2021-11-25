// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionComponent.h"
#include "Zipline.h"
#include "ZiplineAttachPoint.generated.h"

UCLASS()
class UE4MECHANICSSANDBOX_API AZiplineAttachPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZiplineAttachPoint();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* attachPointMesh;

	UPROPERTY(VisibleAnywhere)
	UInteractionComponent* interactionComponent;

	AZipline* ziplineToAttachTo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnInteract();

};
