// Fill out your copyright notice in the Description page of Project Settings.

#include "Intro1.h"
#include "DebugUtils.h"

void UDebugUtils::ForceCrash(const FString& Msg)
{
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogTemp, Fatal, TEXT("%s"), *Msg);
#endif
}

void UDebugUtils::ConsoleLog(const FString& Msg)
{
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogTemp, Log, TEXT("%s"), *Msg);
#endif
}

void UDebugUtils::ConsoleWarning(const FString& Msg)
{
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
#endif
}

void UDebugUtils::ConsoleError(const FString& Msg)
{
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogTemp, Error, TEXT("%s"), *Msg);
#endif
}

void UDebugUtils::ScreenLog(const FString& Msg)
{
	PrintScreen(Msg, FColor::White);
}

void UDebugUtils::ScreenWarning(const FString& Msg)
{
	PrintScreen(Msg, FColor::Yellow);
}

void UDebugUtils::ScreenError(const FString& Msg)
{
	PrintScreen(Msg, FColor::Red);
}

void UDebugUtils::ScreenClear()
{
#ifdef UE_BUILD_DEBUG
	if (GEngine)
	{
		GEngine->ClearOnScreenDebugMessages();
	}
#endif
}

void UDebugUtils::PrintScreen(const FString& Msg, const FColor& Color)
{
#ifdef UE_BUILD_DEBUG
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.5, Color, Msg);
	}
#endif
}
