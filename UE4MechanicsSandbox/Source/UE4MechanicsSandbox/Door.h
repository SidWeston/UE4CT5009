// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathVectorCommon.h"
#include "Components/BoxComponent.h"
#include "Door.generated.h"

UCLASS()
class UE4MECHANICSSANDBOX_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	FRotator targetRotation;

	UPROPERTY(VisibleAnywhere)
	FRotator openRotation;

	UPROPERTY(VisibleAnywhere)
	FRotator closedRotation;

	float openDoorTimer = 0.0f;

	bool shouldOpen = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//door begin and end overlap function definitions
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere);
	UStaticMeshComponent* doorMesh;

	UPROPERTY(VisibleAnywhere);
	UBoxComponent* boxTrigger;

};
