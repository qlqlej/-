#pragma once

#include "EngineMinimal.h"
#include "EngineGlobals.h"  
#include "DestructibleComponent.h"
#include "Engine.h"
#include "Engine/AssetManager.h" 
#include "Runtime/Engine/Classes/Engine/GameEngine.h" 
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NavigationSystem/Public/NavigationPath.h" 
#include "Engine/DataTable.h"  // 추가

UENUM(BlueprintType, Meta = (Bitflags))
enum class Emonster_anim : uint8
{
    Idle,
    Run,
    Attack,
    Skill,
    Hit,
    Death
};


DECLARE_LOG_CATEGORY_EXTERN(Space_coin, Log, All);
#define	LOG_CALLINFO (FString(__FUNCTION__) + TEXT("{") + FString::FromInt(__LINE__) + TEXT("}"))
#define	LOG(Format, ...) 

void PrintViewport(float time, const FColor& color, const FString& text);  // 디버깅용 함수. 
