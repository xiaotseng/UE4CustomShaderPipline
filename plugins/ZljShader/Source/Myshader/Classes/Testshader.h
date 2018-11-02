#pragma once
#include "CoreMinimal.h"
#include "Uobject/ObjectMacros.h"
#include "Classes/Kismet/BlueprintFunctionLibrary.h"
#include "Testshader.generated.h"

UCLASS(meta=(ScriptName="TestShaderLibary"))
class MYSHADER_API UTestShaderBlueprintLibrary:public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
public:
		//UTestShaderBlueprintLibrary(const FObjectInitializer& ObjectInitializer);
		UFUNCTION(BlueprintCallable, Category = "ShaderTestPlugin", meta = (WorldContext = "WorldContextObject"))
		static void DrawTestShaderRenderTarget(class UTextureRenderTarget2D* OutputRenderTarget, AActor* Ac, FLinearColor MyColor, class UTexture* MyTexture);

};