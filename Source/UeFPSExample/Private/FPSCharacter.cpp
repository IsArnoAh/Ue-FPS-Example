// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//应用摄像机
	FPSCameraComponent=CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	//摄像机附着到胶囊体
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent,UCapsuleComponent>(GetCapsuleComponent()));
	//摄像机位置设置
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f,0.0f,50.0f+BaseEyeHeight));
	//启用围绕Pawn旋转
	FPSCameraComponent->bUsePawnControlRotation=true;
	
	//为玩家创建第一人称网格体组件
	FPSMesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);
	//设置仅玩家可见网格体
	FPSMesh->SetOnlyOwnerSee(true);
	//将FPS网格体附着到FPS摄像机
	FPSMesh->SetupAttachment(FPSCameraComponent);
	//调节阴影，实现单个网格体的视觉效果
	FPSMesh->bCastDynamicShadow=false;
	FPSMesh->CastShadow=false;
	//隐藏玩家的第三人称网格体
	GetMesh()->SetOwnerNoSee(true);
	
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(1,5.0f,FColor::Blue,TEXT("player load succeed"));
	
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//绑定控制方向轴映射
	PlayerInputComponent->BindAxis("MoveForward",this,&AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&AFPSCharacter::MoveRight);
	//镜头移动绑定
	PlayerInputComponent->BindAxis("Turn",this,&AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&AFPSCharacter::AddControllerPitchInput);
	//操作Jump绑定
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&AFPSCharacter::StopJump);
	//操作Fire绑定
	PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&AFPSCharacter::Fire);
}
//前后移动实现
void AFPSCharacter::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}
//左右移动实现
void AFPSCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}
//按下跳跃键（空格）
void AFPSCharacter::StartJump()
{
	bPressedJump=true;
}
//放开跳跃键
void AFPSCharacter::StopJump()
{
	bPressedJump=false;
}

void AFPSCharacter::Fire()
{
	//尝试发射子弹
	if (BulletsClass)
	{
		//获取摄像机位置
		FVector CamerLocation;
		FRotator CamerRotation;
		GetActorEyesViewPoint(CamerLocation,CamerRotation);
		//设置MuzzleOffset，发射位置与摄像机的偏移
		MuzzleOffset.Set(200.0f,0.0f,-20.0f);
		//将MuzzleOffset从摄像机空间变化到场景空间
		FVector MuzzleLocation=CamerLocation + FTransform(CamerRotation).TransformVector(MuzzleOffset);
		//将目标方向向上偏移
		FRotator MuzzleRotating=CamerRotation;
		MuzzleRotating.Pitch+=0.0f;
		
		UWorld* World=GetWorld();//获取当前地图
		if (World)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner=this;//生成玩家参数
			SpawnParameters.Instigator=GetInstigator();//获取参数启动状态
			//在偏移点生成子弹
			AFPSBullets* Bullets=World->SpawnActor<AFPSBullets>(BulletsClass,MuzzleLocation,MuzzleRotating,SpawnParameters);
			if (Bullets)//生成子弹成功，设置子弹轨迹参数
			{
				Bullets->FireInDirection(MuzzleRotating.Vector());
			}
			
		}
	}
}





