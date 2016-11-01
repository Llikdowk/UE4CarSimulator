// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "DebugUtils.h"
#include "MyVehicleMovement.generated.h"

/**
 * 
 */

USTRUCT()
struct FGearInfo {
    GENERATED_USTRUCT_BODY();

    UPROPERTY(EditAnywhere)
    float Ratio;
    UPROPERTY(EditAnywhere)
    float DecraseAt;
    UPROPERTY(EditAnywhere)
    float IncreaseAt;
};

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
    void IncreaseGear();
    UFUNCTION(BlueprintCallable, Category = "PhysicsVehicle|Movement")
    void DecreaseGear();
	UFUNCTION(BlueprintCallable, Category = "PhysicsVehicle|Movement")
	void Clutch();
	UFUNCTION(BlueprintCallable, Category = "PhysicsVehicle|Movement")
	void Declutch();

    UFUNCTION(BlueprintCallable, Category = "PhysicsVehicle|Info")
    float GetRpm() { return EngineRpm; }
    UFUNCTION(BlueprintCallable, Category = "PhysicsVehicle|Info")
    int GetCurrentGear() { return CurrentGear; }

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    void ApplyMovement(float DeltaTime);
    void DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos);

	UPROPERTY(EditAnywhere)
    float SteeringPower = 2.0f;

    UPROPERTY(EditAnywhere, DisplayName="Mass (kg)")
    float Mass = 1.0f;

    // forces (N/m)
    UPROPERTY(EditAnywhere, DisplayName="Aerodynamic Drag")
    float AerodynamicDrag;
    UPROPERTY(EditAnywhere, DisplayName="Rolling Resistance")
    float RollingResistance;
    UPROPERTY(EditAnywhere, DisplayName = "Wheel Radius (m)")
    float WheelRadius = 0.228f;

    UPROPERTY(EditAnywhere, DisplayName="Brake")
    float Brake = 1.0;

    UPROPERTY(EditAnywhere)
    UCurveFloat* EngineTorqueCurve;
	UPROPERTY(EditAnywhere)
	UCurveFloat* EngineRpmCurve;

    UPROPERTY(EditAnywhere)
    float CorneringStiffness = 1.0f;

	UPROPERTY(EditAnywhere)
	float ClutchTimeDistension = 0.75f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool AutomaticGearMode = true;
    UPROPERTY(EditAnywhere)
    TArray<FGearInfo> GearBox;
    UPROPERTY(EditAnywhere)
    float FinalDriveRatio = 3.44f;
    UPROPERTY(EditAnywhere) // Currently useless
    float MaxEngineRpm = 8000;


private:
    float InputThrottle;
    float InputSteering;
    void CalcThrottle(float DeltaTime);
    void CalcSteering(float DeltaTime);
    void AutomaticGearChange();

    const float m_to_cm = 100.0f;
    const float rpm_to_radps = 2.0f * PI / 60.0f;
    const float radps_to_rpm = 60.0f / (2.0f * PI);

    FVector Acceleration = FVector::ZeroVector; 
    float TorqueEngine;
    float TorqueWheels;
    
    float EngineRpm = 0.0f;
    float WheelsRpm = 0.0f;

    int CurrentGear;
	bool bClutch = true;
	float TimeAcceleratorPressedWhileClutching = 0.0f;
};

