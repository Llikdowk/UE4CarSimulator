// Fill out your copyright notice in the Description page of Project Settings.

#include "Intro1.h"
#include "CustomPawn.h"


// Sets default values
ACustomPawn::ACustomPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create a dummy root component we can attach things to.
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    // Create a camera and a visible object
    UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
    OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
    // Attach our camera and visible object to our root component. Offset and rotate the camera.
    OurCamera->SetupAttachment(RootComponent);
    OurCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
    OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
    OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACustomPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    // Handle growing and shrinking based on our "Grow" action
    {
        float CurrentScale = OurVisibleComponent->GetComponentScale().X;
        if (bGrowing)
        {
            // Grow to double size over the course of one second
            CurrentScale += DeltaTime;
        }
        else
        {
            // Shrink half as fast as we grow
            CurrentScale -= (DeltaTime * 0.5f);
        }
        // Make sure we never drop below our starting size, or increase past double size.
        CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
        OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));
    }

    // Handle movement based on our "MoveX" and "MoveY" axes
    {
        if (!CurrentVelocity.IsZero())
        {
            FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
            SetActorLocation(NewLocation);
        }
    }

}

// Called to bind functionality to input
void ACustomPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

void ACustomPawn::Move_XAxis(float AxisValue)
{
    // Move at 100 units per second forward or backward
    CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void ACustomPawn::Move_YAxis(float AxisValue)
{
    // Move at 100 units per second right or left
    CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void ACustomPawn::StartGrowing()
{
    bGrowing = true;
}

void ACustomPawn::StopGrowing()
{
    bGrowing = false;
}



