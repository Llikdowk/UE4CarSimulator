// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "DebugUtils.generated.h"

/**
 *
 */

UCLASS()
class INTRO1_API UDebugUtils : public UObject
{
    GENERATED_BODY()

public:

	static void ConsoleLog(const FString&);
	static void ConsoleWarning(const FString&);
	static void ConsoleError(const FString&);

	static void ScreenLog(const FString& Msg);
	static void ScreenWarning(const FString& Msg);
	static void ScreenError(const FString& Msg);
	static void ScreenClear();

	static void ForceCrash(const FString& Msg = "Crash forced!");

private:

	static FORCEINLINE void PrintScreen(const FString&, const FColor&);

};
