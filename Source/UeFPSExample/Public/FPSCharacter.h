// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//引入摄像机和胶囊体头文件
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "FPSBullets.h"
#include "FPSCharacter.generated.h"



UCLASS()
class UEFPSEXAMPLE_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//前后移动函数声明
	UFUNCTION()
	void MoveForward(float Value);
	//左右移动函数声明
	UFUNCTION()
	void MoveRight(float Value);

	//声明跳跃函数
	UFUNCTION()
	void StartJump();
	//释放跳跃函数声明
	UFUNCTION()
	void StopJump();

	//声明发射子弹函数
	UFUNCTION()
	void Fire();

	//发射位置相对于摄像机偏移
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Gameplay)
	FVector MuzzleOffset;

	//生成子弹类
	UPROPERTY(EditDefaultsOnly,Category=Bullets)
	TSubclassOf<class AFPSBullets> BulletsClass;

	//FPS摄像机配置
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	//第一人称网格体，仅玩家可见
	UPROPERTY(VisibleDefaultsOnly,Category=Mesh)
	USkeletalMeshComponent* FPSMesh;

	
};
