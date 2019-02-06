// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ExperimentalGame2GameMode.h"
#include "ExperimentalGame2Character.h"
#include "UObject/ConstructorHelpers.h"

AExperimentalGame2GameMode::AExperimentalGame2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
