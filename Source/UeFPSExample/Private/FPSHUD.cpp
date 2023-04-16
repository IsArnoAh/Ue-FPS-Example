// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSHUD.h"

void AFPSHUD::DrawHUD()
{
	Super::DrawHUD();
	//找出画布中心
	FVector2D Center(Canvas->ClipX*0.5f,Canvas->ClipY);
	//偏移纹理大小一半，以便纹理中心与画布中心对其
	FVector2D CrossHairDrawPosition(Center.X-(CrosshairTexture->GetSurfaceWidth() * 0.5f),Canvas->ClipY * 0.5f - CrosshairTexture->GetSurfaceHeight());
	FCanvasTileItem TileItem(CrossHairDrawPosition,CrosshairTexture->Resource,FLinearColor::Red);
	TileItem.BlendMode=SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}

