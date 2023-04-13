// Copyright Epic Games, Inc. All Rights Reserved.


#include "UeFPSExampleGameModeBase.h"
//实现StartPlay
void AUeFPSExampleGameModeBase::StartPlay()
{
	Super::StartPlay();
	check(GEngine !=nullptr);
	//输出调试消息为5秒，-1防止更新颜色为绿色
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,"Hello World,this is FPSExample");
}

