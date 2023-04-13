// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UeFPSExampleGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UEFPSEXAMPLE_API AUeFPSExampleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	//声明一个启动函数方法
	virtual void StartPlay() override;
};
