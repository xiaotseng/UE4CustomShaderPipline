// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ZljFunctionLIb.generated.h"

/**
 * 
 */
UCLASS()
class MYSHADER_API UZljFunctionLIb : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable, Category = "BakeTexture", meta = (WorldContext = "WorldContextObject"))
		static void bake(class UStaticMesh* ToBakMesh,class UTextureRenderTarget2D* OutRenderTarget);
	
	
	
	
};
