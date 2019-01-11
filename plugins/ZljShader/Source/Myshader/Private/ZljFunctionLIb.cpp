// Fill out your copyright notice in the Description page of Project Settings.
#include "ZljFunctionLIb.h"
#include "Classes/Engine/TextureRenderTarget2D.h"  
#include "Classes/Engine/World.h"  
#include "Classes/Engine/StaticMesh.h"
#include "Public/PipelineStateCache.h"  
#include "Public/RHIStaticStates.h"  
#include "Public/SceneUtils.h"  
#include "Public/SceneInterface.h"  
#include "Public/ShaderParameterUtils.h"  
#include "Public/Logging/MessageLog.h"  
#include "Public/Internationalization/Internationalization.h"  
#include "Public/StaticBoundShaderState.h" 
#include "Engine.h"
#include <iostream>

#include "MyBakeShader.h"//着色器

//绘制函数
static void Draw_ThreadFunction
(
	FRHICommandListImmediate& RHICmdList,
	FTextureRenderTargetResource* OutputRenderTargetResource,
	ERHIFeatureLevel::Type FeatureLevel,
	UStaticMesh * ToBakMesh
	)

{
	check(IsInRenderingThread());//检查是不是渲染线程在调用这个函数
	//////
	const FStaticMeshLODResources &MehshSource= ToBakMesh->GetLODForExport(0);//几何信息
	const FStaticMeshVertexBuffers &MeshBuffers=MehshSource.VertexBuffers;//顶点buffers
	TArray<uint32> indices;
	MehshSource.IndexBuffer.GetCopy(indices);
	uint32 verCount = MehshSource.GetNumVertices();
	TArray< ZLJ::MyVertex> vertices;
	vertices.SetNum(verCount);
	for (uint32 i = 0; i < verCount; i++)
	{
		vertices[i].Position = MehshSource.VertexBuffers.PositionVertexBuffer.VertexPosition(i);
		//vertices[i].VertexColor = MehshSource.VertexBuffers.ColorVertexBuffer.VertexColor(i);
		vertices[i].Uv1 = MehshSource.VertexBuffers.StaticMeshVertexBuffer.GetVertexUV(i, 0);
		vertices[i].Uv2 = MehshSource.VertexBuffers.StaticMeshVertexBuffer.GetVertexUV(i, 1);
	}
	///////////////
	uint32 vertCount = vertices.Num();
	uint32 primitCount = indices.Num()/3;
	void* pIBO = indices.GetData();
	uint32 IBO_Size = indices.GetTypeSize();
	void* pVBO = vertices.GetData();
	uint32 VBO_Size = vertices.GetTypeSize();
	/////////////////
	FTextureRHIRef zRHI;
	//准备绘制
	FTextureRHIRef renderTarget = OutputRenderTargetResource->GetRenderTargetTexture();
	SetRenderTarget(//指定输出到哪里
		RHICmdList,
		renderTarget,
		zRHI,
		ESimpleRenderTargetMode::EUninitializedColorAndDepth,
		FExclusiveDepthStencil::DepthNop_StencilNop

	);

	///////////////////////////////
	TShaderMap<FGlobalShaderType>* GlobalShaderMap = GetGlobalShaderMap(FeatureLevel);//取得着色器集合
	//从一个shaderMap（GlobalShaderMap）使用请求的色器类型（FShaderTestVS）初始化的参照
	TShaderMapRef<FBakeShaderVS> VertexShader(GlobalShaderMap);//初始FShaderTestVS着色器到集合
	TShaderMapRef<FBakeShaderPS> PixelShader(GlobalShaderMap);//初始FShaderTestPS着色器到集合
	/////////////////////
	FVertexLayoutBake VertexDec;//维护一个顶点布局
	VertexDec.InitRHI();
	//管线状态初始化对像
	FGraphicsPipelineStateInitializer GraphicsPSOInit;
	RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
	GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
	GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
	GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
	GraphicsPSOInit.PrimitiveType = PT_TriangleList;
	GraphicsPSOInit.BoundShaderState.VertexShaderRHI = GETSAFERHISHADER_VERTEX(*VertexShader);//设置渲染管线的顶点着色器
	GraphicsPSOInit.BoundShaderState.PixelShaderRHI = GETSAFERHISHADER_PIXEL(*PixelShader);//设置渲染管线的片断着色器
	GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = VertexDec.VertexDeclarationRHI;//设置顶点布局
	SetGraphicsPipelineState(RHICmdList,GraphicsPSOInit);
	//调用绘制基础图元
	
	
	DrawIndexedPrimitiveUP(
		RHICmdList,
		PT_TriangleList,
		0, 
		vertCount,//顶点数
		primitCount,//画几个图元
		pIBO,//IBO
		IBO_Size,//单个IBO大小
		pVBO, //VBO
		VBO_Size//单个VBO大小
	);
	//拷贝数据到传入的渲染目标
	RHICmdList.CopyToResolveTarget(OutputRenderTargetResource->GetRenderTargetTexture(), OutputRenderTargetResource->TextureRHI, FResolveParams());
	
}



/////蓝图调用的函数
void UZljFunctionLIb::bake(UStaticMesh * ToBakMesh, UTextureRenderTarget2D * OutRenderTarget, AActor* ac)
{

	TMap<FVector, FColor> vertextColor;
	ToBakMesh->GetVertexColorData(vertextColor);
	ToBakMesh->GetLODForExport(0).VertexBuffers.PositionVertexBuffer.VertexBufferRHI;
	FTextureRHIParamRef MyTextureRHI= OutRenderTarget->TextureReference.TextureReferenceRHI;
	 const FStaticMeshLODResources &MehshSource=ToBakMesh->GetLODForExport(0);
	 FTextureRenderTargetResource* TextureRenderTargetResource = OutRenderTarget->GameThread_GetRenderTargetResource();
	 const FColorVertexBuffer &colorBuf=MehshSource.VertexBuffers.ColorVertexBuffer;
	 FString name=MehshSource.VertexBuffers.PositionVertexBuffer.GetFriendlyName();
	 ERHIFeatureLevel::Type FeatureLevel=ac->GetWorld()->Scene->GetFeatureLevel();
	 if (GEngine)
	 {
		 GEngine->AddOnScreenDebugMessage(0, 1, FColor::Blue, name, true);
	 }

	 ENQUEUE_RENDER_COMMAND(CaptureCommand)
		 (//传入一个lambda
		 [TextureRenderTargetResource, FeatureLevel, ToBakMesh](FRHICommandListImmediate& RHICmdList)
			{
				Draw_ThreadFunction(RHICmdList, TextureRenderTargetResource, FeatureLevel, ToBakMesh);
			}
		);
}
