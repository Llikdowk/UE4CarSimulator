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
    TotalForces += -AerodynamicDrag * Velocity * Velocity.Size(); // N/m * m/s -> N/s
    TotalForces += -RollingResistance * Velocity;
    if (InputThrottle > 0) {
        float Traction = EngineTorqueCurve->GetFloatValue(Rpm);        
        TotalForces += InputThrottle * Traction * ForwardV;
    }
    else {
        TotalForces += InputThrottle * Brake * ForwardV;
    }

    
    Acceleration = TotalForces*DeltaTime / Mass; // m/s^2
    Velocity = Velocity + Acceleration * DeltaTime; // m/s
    Rpm = Velocity.Size() / (WheelRadius * 2 * 3.141592f) * 60.0f;
    FVector Position = PawnOwner->GetActorLocation();
    FVector NewPosition = Position + Velocity*m_to_cm * DeltaTime;
    PawnOwner->SetActorLocation(NewPosition);
    
    DrawDebugLine(GetWorld(), PawnOwner->GetActorLocation(), PawnOwner->GetActorLocation() + ForwardV*1000.0f, FColor::Cyan, false, -1.0f, (uint8)'\000', 5.0f);
    DrawDebugLine(GetWorld(), PawnOwner->GetActorLocation(), PawnOwner->GetActorLocation() + Velocity*100.0f, FColor::Red, false, -1.0f, (uint8)'\000', 10.0f);

    UE_LOG(LogTemp, Warning, TEXT("rpm=%s"), *(FString::SanitizeFloat(Rpm)));
}

void UMyVehicleMovement::CalcSteering(float DeltaTime) {
    PawnOwner->AddActorLocalRotation(FQuat(FVector::UpVector, InputSteering * SteeringPower * DeltaTime), true);
    
}

void UMyVehicleMovement::ApplyMovement(float DeltaTime) {
    CalcSteering(DeltaTime);
    CalcThrottle(DeltaTime);
    MoveUpdatedComponent(GetPendingInputVector(), PawnOwner->GetActorRotation(), false);
}
