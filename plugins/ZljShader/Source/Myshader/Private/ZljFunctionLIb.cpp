// Fill out your copyright notice in the Description page of Project Settings.
#include "ZljFunctionLIb.h"
#include "Engine.h"

#include "Classes/Engine/TextureRenderTarget2D.h"  
#include "Classes/Engine/World.h"  
#include "Public/GlobalShader.h"  
#include "Public/PipelineStateCache.h"  
#include "Public/RHIStaticStates.h"  
#include "Public/SceneUtils.h"  
#include "Public/SceneInterface.h"  
#include "Public/ShaderParameterUtils.h"  
#include "Public/Logging/MessageLog.h"  
#include "Public/Internationalization/Internationalization.h"  
#include "Public/StaticBoundShaderState.h"  

//绘制函数
static void Draw_ThreadFunction
	(
		FRHICommandListImmediate& RHICmdList,
		UTextureRenderTarget2D * OutRenderTarget,
		const FStaticMeshLODResources &MehshSource//几何信息
	)
{
	//////
	check(IsInRenderingThread());
	FTextureRHIParamRef TextureRHI = OutRenderTarget->TextureReference.TextureReferenceRHI;
	const FStaticMeshVertexBuffers &MeshBuffers=MehshSource.VertexBuffers;//顶点buffers
	FStaticMeshVertexBuffer fee;
	//DrawIndexedPrimitiveUP(RHICmdList,PT_TriangleList,0,4,6)
}



/////蓝图调用的函数
void UZljFunctionLIb::bake(UStaticMesh * ToBakMesh, UTextureRenderTarget2D * OutRenderTarget)
{

	TMap<FVector, FColor> vertextColor;
	ToBakMesh->GetVertexColorData(vertextColor);
	uint32 n= vertextColor.GetAllocatedSize();
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Cyan, FString::FromInt(n), true);
	//取得mesh三角形数量
	
	 const FStaticMeshLODResources &MehshSource=ToBakMesh->GetLODForExport(0);
	 FPositionVertexBuffer b = MehshSource.VertexBuffers.PositionVertexBuffer;

	 /*
	 //压入绘制命令
	 ENQUEUE_RENDER_COMMAND(CaptureCommand)
		 (
		 [OutRenderTarget,&MehshSource](FRHICommandListImmediate& RHICmdList)
			{
				Draw_ThreadFunction(RHICmdList, OutRenderTarget, MehshSource);
			}
		);
		*/
	//GEngine->AddOnScreenDebugMessage(0, 1, FColor::Cyan, FString::FromInt(n), true);
}
