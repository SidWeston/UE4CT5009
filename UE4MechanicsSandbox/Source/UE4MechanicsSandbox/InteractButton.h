// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionComponent.h"
#include "InteractButton.generated.h"

UCLASS()
class UE4MECHANICSSANDBOX_API AInteractButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractButton();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* buttonBackground;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* buttonObject;

	UPROPERTY(VisibleAnywhere)
	bool buttonPressed;

	UPROPERTY(VisibleAnywhere)
	UInteractionComponent* interactionComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnButtonPressed();

};
