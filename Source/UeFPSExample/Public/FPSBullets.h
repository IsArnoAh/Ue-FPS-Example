// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"//引入球体组件
#include "GameFramework/ProjectileMovementComponent.h"//引入移动组件
#include "FPSBullets.generated.h"


UCLASS()
class UEFPSEXAMPLE_API AFPSBullets : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSBullets();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//球体碰撞组件
	UPROPERTY(VisibleAnywhere,Category=Bullets)
	USphereComponent* CollisionComponent;

	//发射移动组件
	UPROPERTY(VisibleAnywhere,Category=Movement)
	UProjectileMovementComponent* BulletsMovementComponent;

	//子弹网格体
	UPROPERTY(VisibleDefaultsOnly,Category=Bullets)
	UStaticMeshComponent* BulletStaticMeshComponent;
	//子弹材质
	UPROPERTY(VisibleDefaultsOnly,Category=Material)
	UMaterialInstanceDynamic* BulletsMaterialInstance;

	//初始发射向上的速度函数
	void FireInDirection(const FVector& shootDirection);
};
