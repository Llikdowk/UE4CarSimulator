// Fill out your copyright notice in the Description page of Project Settings.

#include "Intro1.h"
#include "MyVehicleMovement.h"
#include "DrawDebugHelpers.h"

UMyVehicleMovement::UMyVehicleMovement() {
}

void UMyVehicleMovement::SetThrottleInput(float InputValue) {
    this->InputThrottle = InputValue;
}

void UMyVehicleMovement::SetSteeringInput(float InputValue) {
    this->InputSteering = InputValue;
}

void UMyVehicleMovement::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMyVehicleMovement::CalcThrottle(float DeltaTime) {

    FVector ForwardV = PawnOwner->GetActorForwardVector();

    FVector TotalForces = FVector::ZeroVector;
    TotalForces += -AerodynamicDrag * Velocity * Velocity.Size(); // N
    TotalForces += -RollingResistance * Velocity.GetSafeNormal();
    if (InputThrottle > 0) {
        TorqueWheels = TorqueEngine * GearBox[CurrentGear].Ratio * FinalDriveRatio;
        float Traction = TorqueWheels / WheelRadius;
        TotalForces += InputThrottle * ForwardV * Traction;
    }
    else {
        TotalForces += InputThrottle * Brake * ForwardV;
    }

    Acceleration = TotalForces / Mass; // m/s^2
    Velocity = Velocity + Acceleration * DeltaTime; // m/s

    WheelsRpm = Velocity.Size() / WheelRadius * radps_to_rpm;
    TorqueEngine = EngineTorqueCurve->GetFloatValue(EngineRpm);
    EngineRpm = GearBox[CurrentGear].Ratio * FinalDriveRatio * Velocity.Size() / WheelRadius * radps_to_rpm;

    UE_LOG(LogTemp, Warning, TEXT("WheelsRPM=%s"), *(FString::SanitizeFloat(WheelsRpm)));
    UE_LOG(LogTemp, Warning, TEXT("EngineRPM=%s"), *(FString::SanitizeFloat(EngineRpm)));
    UE_LOG(LogTemp, Warning, TEXT("GEAR=%s"), *(FString::SanitizeFloat(CurrentGear)));

    FVector Position = PawnOwner->GetActorLocation();
    FVector NewPosition = Position + Velocity*m_to_cm * DeltaTime;
    PawnOwner->SetActorLocation(NewPosition);
    
    DrawDebugLine(GetWorld(), PawnOwner->GetActorLocation(), PawnOwner->GetActorLocation() + ForwardV*1000.0f, FColor::Cyan, false, -1.0f, (uint8)'\000', 5.0f);
    DrawDebugLine(GetWorld(), PawnOwner->GetActorLocation(), PawnOwner->GetActorLocation() + Velocity*100.0f, FColor::Red, false, -1.0f, (uint8)'\000', 10.0f);
}

void UMyVehicleMovement::IncreaseGear() {
    if (CurrentGear == GearBox.Num() - 1) return;

    ++CurrentGear;
}

void UMyVehicleMovement::DecreaseGear() {
    if (CurrentGear == 0) return;

    --CurrentGear;
    EngineRpm = FMath::Min(MaxEngineRpm, EngineRpm); // fixme! velocity should drop
}

void UMyVehicleMovement::CalcSteering(float DeltaTime) {
    PawnOwner->AddActorLocalRotation(FQuat(FVector::UpVector, InputSteering * SteeringPower * DeltaTime), true);
    
}

void UMyVehicleMovement::AutomaticGearChange() {
    if (!AutomaticGearMode) return;

    FGearInfo GearInfo = GearBox[CurrentGear];
    float CurrentRatio = EngineRpm / MaxEngineRpm;
    if (CurrentRatio > GearInfo.IncreaseAt) {
        IncreaseGear();
    }
    else if (CurrentRatio < GearInfo.DecraseAt) {
        DecreaseGear();
    }
}

void UMyVehicleMovement::ApplyMovement(float DeltaTime) {
    CalcSteering(DeltaTime);
    CalcThrottle(DeltaTime);
    AutomaticGearChange();
    MoveUpdatedComponent(GetPendingInputVector(), PawnOwner->GetActorRotation(), false);
}

// info: https://github.com/EpicGames/UnrealEngine/blob/c9f4efe690de8b3b72a11223865c623ca0ee7086/Engine/Source/Runtime/Engine/Private/Actor.cpp#L1797
void UMyVehicleMovement::DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos) {
	UFont* RenderFont = GEngine->GetSmallFont();
    Canvas->DrawText(RenderFont, FString::Printf(TEXT("Gear: %s"), *(FString::FromInt(CurrentGear))), 4.0f, YPos);
}