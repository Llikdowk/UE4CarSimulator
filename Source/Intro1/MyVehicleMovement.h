// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "MyVehicleMovement.generated.h"

/**
 * 
 */
UCLASS()
class INTRO1_API UMyVehicleMovement : public UPawnMovementComponent
{
	GENERATED_BODY()


public:
 
    UMyVehicleMovement();

    UFUNCTION(BlueprintCallable, Category="PhysicsVehicle|Movement")
    void SetThrottleInput(float InputThrottle);
    UFUNCTION(BlueprintCallable, Category="PhysicsVehicle|Movement")
    void SetSteeringInput(float InputSteering);

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    void ApplyMovement(float DeltaTime);

    /* DEPRECATED */
    UPROPERTY(EditAnywhere)
    float Throttle = 10.0f;
    UPROPERTY(EditAnywhere)
    float Friction = 5.0f;
    UPROPERTY(EditAnywhere)
    float SteeringPower = 2.0f;
    /**/

    UPROPERTY(EditAnywhere)
    float Mass = 1.0f;

    // forces
    UPROPERTY(EditAnywhere)
    float AerodynamicDrag;
    UPROPERTY(EditAnywhere)
    float RollingResistance;
    UPROPERTY(EditAnywhere)
    float Traction = 1.0;
    UPROPERTY(EditAnywhere)
    float Brake = 1.0;

    UPROPERTY(EditAnywhere)
    float CorneringStiffness = 1.0f;

private:
    float InputThrottle;
    float InputSteering;
    void CalcThrottle(float DeltaTime);
    void CalcSteering(float DeltaTime);

    FVector Velocity = FVector::ZeroVector;
    FVector Acceleration = FVector::ZeroVector; 

};
