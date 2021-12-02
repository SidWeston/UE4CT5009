// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "LevelChangePoint.generated.h"

UCLASS()
class UE4MECHANICSSANDBOX_API ALevelChangePoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelChangePoint();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* pointMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* pointTrigger;

	UPROPERTY(EditAnywhere)
	FName levelName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
