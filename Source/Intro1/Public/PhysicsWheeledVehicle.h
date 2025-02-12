// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "MyVehicleMovement.h"
#include "PhysicsWheeledVehicle.generated.h"

UCLASS()
class INTRO1_API APhysicsWheeledVehicle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APhysicsWheeledVehicle();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent*) override;

    UPROPERTY(EditAnywhere)
    USkeletalMeshComponent* Mesh;
    UPROPERTY(EditAnywhere)
    UMyVehicleMovement* VehicleMovement;

    virtual void APhysicsWheeledVehicle::DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos) override;
};
