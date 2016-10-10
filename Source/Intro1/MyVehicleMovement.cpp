// Fill out your copyright notice in the Description page of Project Settings.

#include "Intro1.h"
#include "MyVehicleMovement.h"
#include "DrawDebugHelpers.h"

UMyVehicleMovement::UMyVehicleMovement() {
//    PrimaryComponentTick.bCanEverTick = true;
//    PrimaryComponentTick.bStartWithTickEnabled = true;
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
    DrawDebugLine(GetWorld(), PawnOwner->GetActorLocation(), PawnOwner->GetActorLocation() + ForwardV*1000.0f, FColor::Cyan, false, -1.0f, (uint8)'\000', 5.0f);
    DrawDebugLine(GetWorld(), PawnOwner->GetActorLocation(), PawnOwner->GetActorLocation() + GetPendingInputVector()*100.0f, FColor::Red, false, -1.0f, (uint8)'\000', 10.0f);
    AddInputVector(ForwardV*InputThrottle*DeltaTime*Throttle);
    int Sign = FMath::Sign(PawnOwner->GetTransform().InverseTransformVector(GetPendingInputVector()).X);
    AddInputVector(-GetPendingInputVector().SafeNormal()*DeltaTime*Friction);

}

void UMyVehicleMovement::CalcSteering(float DeltaTime) {
    PawnOwner->AddActorLocalRotation(FQuat(FVector::UpVector, InputSteering * SteeringPower * DeltaTime), true);
}

void UMyVehicleMovement::ApplyMovement(float DeltaTime) {
    CalcSteering(DeltaTime);
    CalcThrottle(DeltaTime);
    MoveUpdatedComponent(GetPendingInputVector(), PawnOwner->GetActorRotation(), false);
}
