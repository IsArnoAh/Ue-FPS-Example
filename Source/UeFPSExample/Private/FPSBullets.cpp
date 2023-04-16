// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBullets.h"

// Sets default values
AFPSBullets::AFPSBullets()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    if (!RootComponent)//如果组件不存在则开始创建组件
    {
	    RootComponent=CreateDefaultSubobject<USceneComponent>(TEXT("BulletsSceneComponet"));
    }
    if (!CollisionComponent)
    {
    	//组装子弹碰撞（碰撞球体）
	    CollisionComponent=CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		//将球体的碰撞文件名称设置为”Bullets“
    	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Bullets"));
    	//子弹命中调用事件
    	CollisionComponent->OnComponentHit.AddDynamic(this,&AFPSBullets::OnHit);
    	//子弹碰撞半径
    	CollisionComponent->InitSphereRadius(15.0f);
    	//组件类型设置为碰撞组件
    	RootComponent=CollisionComponent;
    }

    if (!BulletsMovementComponent)
    {
	    //使用组件驱动发射子弹
    	BulletsMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletsMovementComponent"));
    	BulletsMovementComponent->SetUpdatedComponent(CollisionComponent);//更新碰撞
    	BulletsMovementComponent->InitialSpeed=3000.0f;//设置初速度
    	BulletsMovementComponent->MaxSpeed=3000.0f;//设置最大速度
    	BulletsMovementComponent->bRotationFollowsVelocity=true;//匹配速度方向
    	BulletsMovementComponent->bShouldBounce=false;//不可反弹
    	BulletsMovementComponent->ProjectileGravityScale=0.0f;//自身重力
    }
	//创建出子弹静态网格体
    if (!BulletStaticMeshComponent)
    {
	    BulletStaticMeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMeshComponent"));
    	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Modle/Sphere.Sphere'"));
    	if(Mesh.Succeeded())
    	{
    		BulletStaticMeshComponent->SetStaticMesh(Mesh.Object);
    	}
	//创建子弹材质
	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/Modle/BulletsMaterial.BulletsMaterial'"));
    if (Material.Succeeded())
    {
    	//加子弹材质添加到静态网格体上
	    BulletsMaterialInstance=UMaterialInstanceDynamic::Create(Material.Object,BulletStaticMeshComponent);
    }
	//材质附着基本参数配置
	BulletStaticMeshComponent->SetMaterial(0,BulletsMaterialInstance);
	BulletStaticMeshComponent->SetRelativeScale3D(FVector(0.09f,0.09f,0.09f));
	BulletStaticMeshComponent->SetupAttachment(RootComponent);
}
	InitialLifeSpan=3.0f;
}


// Called when the game starts or when spawned
void AFPSBullets::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSBullets::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//子弹发射向上偏移函数
void AFPSBullets::FireInDirection(const FVector& shootDirection)
{
	BulletsMovementComponent->Velocity=shootDirection * BulletsMovementComponent->InitialSpeed;
}
//子弹发射调用函数
void AFPSBullets::OnHit(UPrimitiveComponent* HItComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormaImpulse, const FHitResult& Hit)
{
	if (OtherActor !=this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(BulletsMovementComponent->Velocity*100.0f,Hit.ImpactNormal);
	}
}



