// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h"

UCLASS()
class AFloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
    
    virtual void PostInitProperties() override;
    virtual void PostEditChangeProperty(FPropertyChangedEvent&) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HeightFactor = 20.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
    int32 TotalDamage = 200;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
    float DamageTimeInSeconds = 1.0f;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "Damage")
    float DamagePerSecond;

    UFUNCTION(BlueprintCallable, Category="Damage")
    void CalculateValues();

    UFUNCTION(BlueprintNativeEvent, Category="Damage")
    void PureBlueprintFunction();

private:
    float RunningTime;
};
