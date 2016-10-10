// Fill out your copyright notice in the Description page of Project Settings.

#include "Intro1.h"
#include "PhysicsWheeledVehicle.h"


// Sets default values
APhysicsWheeledVehicle::APhysicsWheeledVehicle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;
    VehicleMovement = CreateDefaultSubobject<UMyVehicleMovement>(TEXT("CustomVehicleMovement"));
    VehicleMovement->SetUpdatedComponent(RootComponent);
}

// Called when the game starts or when spawned
void APhysicsWheeledVehicle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APhysicsWheeledVehicle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    
    VehicleMovement->ApplyMovement(DeltaTime);
}

// Called to bind functionality to input
void APhysicsWheeledVehicle::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

