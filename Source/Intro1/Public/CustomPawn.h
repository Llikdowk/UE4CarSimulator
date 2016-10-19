// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "CustomPawn.generated.h"

UCLASS()
class INTRO1_API ACustomPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACustomPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

    UPROPERTY(EditAnywhere)
    USceneComponent* OurVisibleComponent;

    //Input functions
    UFUNCTION(BlueprintCallable, Category="CustomPawn/Input")
    void Move_XAxis(float AxisValue);
    UFUNCTION(BlueprintCallable, Category="CustomPawn/Input")
    void Move_YAxis(float AxisValue);
    UFUNCTION(BlueprintCallable, Category="CustomPawn/Input")
    void StartGrowing();
    UFUNCTION(BlueprintCallable, Category="CustomPawn/Input")
    void StopGrowing();

    //Input variables
    FVector CurrentVelocity;
    bool bGrowing;
	
};
