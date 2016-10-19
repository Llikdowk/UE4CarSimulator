// Fill out your copyright notice in the Description page of Project Settings.

#include "Intro1.h"
#include "FloatingActor.h"


// Sets default values
AFloatingActor::AFloatingActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector NewLocation = GetActorLocation();
    float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
    NewLocation.Z += DeltaHeight * HeightFactor;       //Scale our height by a factor of 20
    RunningTime += DeltaTime;
    SetActorLocation(NewLocation);

    PureBlueprintFunction();
}

void AFloatingActor::CalculateValues()
{
    DamagePerSecond = TotalDamage / DamageTimeInSeconds;
}

void AFloatingActor::PostInitProperties()
{
    Super::PostInitProperties();
    DamagePerSecond = TotalDamage / DamageTimeInSeconds;
    CalculateValues();
}

#if WITH_EDITOR
void AFloatingActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    CalculateValues();
    Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void AFloatingActor::PureBlueprintFunction_Implementation()
{

    //UE_LOG(LogTemp, Warning, TEXT("Hello there! default cpp implementation for PrueBlueprintFunction running"));
}
