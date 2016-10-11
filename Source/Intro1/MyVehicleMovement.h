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
    UFUNCTION(BlueprintCallable, Category = "PhysicsVehicle|Movement")
    void UpGear();
    UFUNCTION(BlueprintCallable, Category = "PhysicsVehicle|Movement")
    void DownGear();

    UFUNCTION(BlueprintCallable, Category = "PhysicsVehicle|Info")
    float GetRpm() { return EngineRpm; }
    UFUNCTION(BlueprintCallable, Category = "PhysicsVehicle|Info")
    int GetCurrentGear() { return CurrentGear; }

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    void ApplyMovement(float DeltaTime);

    /* DEPRECATED */
    float SteeringPower = 2.0f;
    /**/

    UPROPERTY(EditAnywhere, DisplayName="Mass (kg)")
    float Mass = 1.0f;

    // forces (N/m)
    UPROPERTY(EditAnywhere, DisplayName="Aerodynamic Drag (N)")
    float AerodynamicDrag;
    UPROPERTY(EditAnywhere, DisplayName="Rolling Resistance (N)")
    float RollingResistance;
    UPROPERTY(EditAnywhere, DisplayName = "Wheel Radius (m)")
    float WheelRadius = 0.228f;

    UPROPERTY(EditAnywhere, DisplayName="Brake (N)")
    float Brake = 1.0;

    UPROPERTY(EditAnywhere)
    UCurveFloat* EngineTorqueCurve;

    UPROPERTY(EditAnywhere)
    float CorneringStiffness = 1.0f;

    UPROPERTY(EditAnywhere)
    //float CurrentGearRatio = 3.82f; //temp, as if the car only had one gear
    TArray<float> GearBox;
    UPROPERTY(EditAnywhere)
    float FinalDriveRatio = 3.44f;
    UPROPERTY(EditAnywhere)
    float MaxEngineRpm = 8000;

    void DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos);

private:
    float InputThrottle;
    float InputSteering;
    void CalcThrottle(float DeltaTime);
    void CalcSteering(float DeltaTime);

    const float m_to_cm = 100.0f;
    const float rpm_to_radps = 2.0f * PI / 60.0f;
    const float radps_to_rpm = 60.0f / (2.0f * PI);

    FVector Acceleration = FVector::ZeroVector; 
    float TorqueEngine;
    float TorqueWheels;
    
    float EngineRpm = 0.0f;
    float WheelsRpm = 0.0f;

    int CurrentGear;
};
