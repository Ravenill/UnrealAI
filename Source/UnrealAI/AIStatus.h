#pragma once

#include "CoreMinimal.h"
#include "AIStatus.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EAIStatus : uint8
{
    STAT_PATROLING  UMETA(DisplayName = "Patroling"),
    STAT_SUSPICIOUS  UMETA(DisplayName = "Suspicious"),
    STAT_INVESTIGATING  UMETA(DisplayName = "Investigating"),
    STAT_ALARMED    UMETA(DisplayName = "Alarmed")
};
