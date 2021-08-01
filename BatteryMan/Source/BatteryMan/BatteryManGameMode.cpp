// Copyright Epic Games, Inc. All Rights Reserved.

#include "BatteryManGameMode.h"
#include "BatteryManCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABatteryManGameMode::ABatteryManGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
