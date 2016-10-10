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
    float SteeringPower = 2.0f;
    /**/

    UPROPERTY(EditAnywhere, DisplayName="Mass (kg)")
    float Mass = 1.0f;

    // forces (N/m)
    UPROPERTY(EditAnywhere, DisplayName="Aerodynamic Drag (N/m)")
    float AerodynamicDrag;
    UPROPERTY(EditAnywhere, DisplayName="Rolling Resistance (N/m)")
    float RollingResistance;
    UPROPERTY(EditAnywhere)
    UCurveFloat* EngineTorqueCurve;
    UPROPERTY(EditAnywhere, DisplayName="Brake (N/m)")
    float Brake = 1.0;
    UPROPERTY(EditAnywhere, DisplayName = "Wheel Radius (m)")
    float WheelRadius = 0.25f;

    UPROPERTY(EditAnywhere)
    float CorneringStiffness = 1.0f;

    // Velocity: m/s
    

    //UPROPERTY(VisibleAnywhere)
    //FVector Velocity = FVector::ZeroVector;

private:
    float InputThrottle;
    float InputSteering;
    void CalcThrottle(float DeltaTime);
    void CalcSteering(float DeltaTime);

    const float m_to_cm = 100.0f;

    FVector Acceleration = FVector::ZeroVector; 
    float Rpm = 0.0f;
};
