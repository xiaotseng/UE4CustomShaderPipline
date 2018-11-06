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

#include "MyBakeShader.h"//着色器


//绘制函数
static void Draw_ThreadFunction
	(
		FRHICommandListImmediate& RHICmdList,
		UTextureRenderTarget2D * OutRenderTarget,
		ERHIFeatureLevel::Type FeatureLevel,
		const FStaticMeshLODResources &MehshSource//几何信息
	)
{
	//////
	FTextureRHIParamRef TextureRHI = OutRenderTarget->TextureReference.TextureReferenceRHI;
	const FStaticMeshVertexBuffers &MeshBuffers=MehshSource.VertexBuffers;//顶点buffers
	FStaticMeshVertexBuffer fee;
	//准备绘制
	check(IsInRenderingThread());
	SetRenderTarget(
		RHICmdList, 
		OutRenderTarget->TextureReference.
	);
	///////////////////////////////
	TShaderMap<FGlobalShaderType>* GlobalShaderMap = GetGlobalShaderMap(FeatureLevel);//取得着色器集合
	//从一个shaderMap（GlobalShaderMap）使用请求的色器类型（FShaderTestVS）初始化的参照
	TShaderMapRef<FBakeShaderVS> VertexShader(GlobalShaderMap);//初始FShaderTestVS着色器到集合
	TShaderMapRef<FBakeShaderPS> PixelShader(GlobalShaderMap);//初始FShaderTestPS着色器到集合
	/////////////////////
	FVertexLayoutBake VertexDec;//顶点布局
	VertexDec.InitRHI();
	//管线状态初始化对像
	FGraphicsPipelineStateInitializer GraphicsPSOInit;
	RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
	GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
	GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
	GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
	GraphicsPSOInit.PrimitiveType = PT_TriangleList;
	//GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GetVertexDeclarationFVector4();
	GraphicsPSOInit.BoundShaderState.VertexShaderRHI = GETSAFERHISHADER_VERTEX(*VertexShader);//设置渲染管线的顶点着色器
	GraphicsPSOInit.BoundShaderState.PixelShaderRHI = GETSAFERHISHADER_PIXEL(*PixelShader);//设置渲染管线的片断着色器
	GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = VertexDec.VertexDeclarationRHI;//设置顶点布局
	SetGraphicsPipelineState(RHICmdList,GraphicsPSOInit);
	//DrawIndexedPrimitiveUP(RHICmdList,PT_TriangleList,0,4,6)
}



/////蓝图调用的函数
void UZljFunctionLIb::bake(UStaticMesh * ToBakMesh, UTextureRenderTarget2D * OutRenderTarget)
{

	TMap<FVector, FColor> vertextColor;
	ToBakMesh->GetVertexColorData(vertextColor);
	ToBakMesh->GetLODForExport(0).VertexBuffers.PositionVertexBuffer.VertexBufferRHI.;
	uint32 n= vertextColor.GetAllocatedSize();
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Cyan, FString::FromInt(n), true);
	//取得mesh三角形数量
	
	 const FStaticMeshLODResources &MehshSource=ToBakMesh->GetLODForExport(0);
	 MehshSource.VertexBuffers.PositionVertexBuffer.GetFriendlyName();

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
