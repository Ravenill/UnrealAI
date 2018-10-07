// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "UnrealAIGameMode.h"
#include "UnrealAIPlayerController.h"
#include "UnrealAICharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealAIGameMode::AUnrealAIGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AUnrealAIPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}