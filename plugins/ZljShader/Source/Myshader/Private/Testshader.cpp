
//控制台变量
//static TAutoConsoleVariable<int32> CVarMyTest(
//	TEXT("r.MyTest"),
//	0,
//	TEXT("Test My Global Shader, set it to 0 to disable, or to 1, 2 or 3 for fun!"),
//	ECVF_RenderThreadSafe
//);
// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.  

#include "TestShader.h"  
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



#define LOCTEXT_NAMESPACE "MyShader"  


class FMyShaderTest : public FGlobalShader
{
public:

	FMyShaderTest() {}

	FMyShaderTest(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FGlobalShader(Initializer)
	{
		//绑定参数到shader
		SimpleColorVal.Bind(Initializer.ParameterMap, TEXT("SimpleColor"));
	}

	static bool ShouldCache(EShaderPlatform Platform)
	{
		//是否要缓存编译代码
		return true;
	}

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		//是否要排序
		//return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM4);  
		return true;
	}

	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		//修改编译环境
		FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
		OutEnvironment.SetDefine(TEXT("TEST_MICRO"), 1);
	}
	//自定义函数用于设置参数
	void SetParameters(
		FRHICommandListImmediate& RHICmdList,
		const FLinearColor &MyColor
	)
	{

		SetShaderValue(RHICmdList, GetPixelShader(), SimpleColorVal, MyColor);
	}

	virtual bool Serialize(FArchive& Ar) override
	{
		//调用父类的虚函数
		bool bShaderHasOutdatedParameters = FGlobalShader::Serialize(Ar);
		Ar << SimpleColorVal;
		return bShaderHasOutdatedParameters;
	}

private:

	FShaderParameter SimpleColorVal;

};

class FShaderTestVS : public FMyShaderTest
{
	//声明shader
	DECLARE_SHADER_TYPE(FShaderTestVS, Global);

public:
	FShaderTestVS() {}

	FShaderTestVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FMyShaderTest(Initializer)
	{

	}
};


class FShaderTestPS : public FMyShaderTest
{
	//声明shader
	DECLARE_SHADER_TYPE(FShaderTestPS, Global);

public:
	FShaderTestPS() {}

	FShaderTestPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FMyShaderTest(Initializer)
	{

	}
};
//实现shader
IMPLEMENT_SHADER_TYPE(, FShaderTestVS, TEXT("/Plugin/ZljShader/Private/MyShader.usf"), TEXT("MainVS"), SF_Vertex)
IMPLEMENT_SHADER_TYPE(, FShaderTestPS, TEXT("/Plugin/ZljShader/Private/MyShader.usf"), TEXT("MainPS"), SF_Pixel)
//自定义的绘制
static void DrawTestShaderRenderTarget_RenderThread(
	FRHICommandListImmediate& RHICmdList,//指令列表
	FTextureRenderTargetResource* OutputRenderTargetResource,//用于容纳渲染结果数据
	ERHIFeatureLevel::Type FeatureLevel,//图形API特性：是一个枚举ES2、ES3_1、SM4、SM5
	FName TextureRenderTargetName,
	FLinearColor MyColor
)
{
	//是否渲染线程在调用
	check(IsInRenderingThread());

#if WANTS_DRAW_MESH_EVENTS  
	FString EventName;
	TextureRenderTargetName.ToString(EventName);
	SCOPED_DRAW_EVENTF(RHICmdList, SceneCapture, TEXT("ShaderTest %s"), *EventName);
#else  
	SCOPED_DRAW_EVENT(RHICmdList, DrawUVDisplacementToRenderTarget_RenderThread);
#endif  

	//设置渲染目标  
	SetRenderTarget(
		RHICmdList,
		OutputRenderTargetResource->GetRenderTargetTexture(),//渲染的内容放在这里
		FTextureRHIRef(),
		ESimpleRenderTargetMode::EUninitializedColorAndDepth,
		FExclusiveDepthStencil::DepthNop_StencilNop
	);

	//设置视口  
	//FIntPoint DrawTargetResolution(OutputRenderTargetResource->GetSizeX(), OutputRenderTargetResource->GetSizeY());  
	//RHICmdList.SetViewport(0, 0, 0.0f, DrawTargetResolution.X, DrawTargetResolution.Y, 1.0f);  
	//不同类型Shader的集合
	TShaderMap<FGlobalShaderType>* GlobalShaderMap = GetGlobalShaderMap(FeatureLevel);//取得着色器集合
	//从一个shaderMap（GlobalShaderMap）使用请求的色器类型（FShaderTestVS）初始化的参照
	TShaderMapRef<FShaderTestVS> VertexShader(GlobalShaderMap);//初始FShaderTestVS着色器到集合
	TShaderMapRef<FShaderTestPS> PixelShader(GlobalShaderMap);//初始FShaderTestPS着色器到集合

	// Set the graphic pipeline state.  设置渲染管线的状态,渲染参数都在这里了
	FGraphicsPipelineStateInitializer GraphicsPSOInit;
	RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);//应用管线状态
	GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
	GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
	GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
	GraphicsPSOInit.PrimitiveType = PT_TriangleList;
	GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GetVertexDeclarationFVector4();
	GraphicsPSOInit.BoundShaderState.VertexShaderRHI = GETSAFERHISHADER_VERTEX(*VertexShader);//设置渲染管线的顶点着色器
	GraphicsPSOInit.BoundShaderState.PixelShaderRHI = GETSAFERHISHADER_PIXEL(*PixelShader);//设置渲染管线的片断着色器
	SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit);

	//RHICmdList.SetViewport(0, 0, 0.0f, DrawTargetResolution.X, DrawTargetResolution.Y, 1.0f);  
	PixelShader->SetParameters(RHICmdList, MyColor);

	// Draw grid.  
	//uint32 PrimitiveCount = 2;  
	//RHICmdList.DrawPrimitive(PT_TriangleList, 0, PrimitiveCount, 1);  //准备要传到shader的值
	//顶点
	FVector4 Vertices[4];
	Vertices[0].Set(-1.0f, 1.0f, 0, 1.0f);
	Vertices[1].Set(1.0f, 1.0f, 0, 1.0f);
	Vertices[2].Set(-1.0f, -1.0f, 0, 1.0f);
	Vertices[3].Set(1.0f, -1.0f, 0, 1.0f);
	static const uint16 Indices[6] =
	{
		0, 1, 2,
		2, 1, 3
	};
	//DrawPrimitiveUP(RHICmdList, PT_TriangleStrip, 2, Vertices, sizeof(Vertices[0]));  
	//绘制指令
	
	DrawIndexedPrimitiveUP(
		RHICmdList,
		PT_TriangleList,
		0,
		ARRAY_COUNT(Vertices),
		2,
		Indices,
		sizeof(Indices[0]),
		Vertices,
		sizeof(Vertices[0])
	);

	// Resolve render target.  拷贝数据
	RHICmdList.CopyToResolveTarget(
		OutputRenderTargetResource->GetRenderTargetTexture(),
		OutputRenderTargetResource->TextureRHI,
		 FResolveParams());
}

//蓝图的构造函数
UTestShaderBlueprintLibrary::UTestShaderBlueprintLibrary(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer) {

}
//蓝图调用的绘制函数
void UTestShaderBlueprintLibrary::DrawTestShaderRenderTarget(
	UTextureRenderTarget2D* OutputRenderTarget,//
	AActor* Ac,
	FLinearColor MyColor
)
{
	check(IsInGameThread());

	if (!OutputRenderTarget)
	{
		return;
	}

	FTextureRenderTargetResource* TextureRenderTargetResource = OutputRenderTarget->GameThread_GetRenderTargetResource();
	UWorld* World = Ac->GetWorld();
	ERHIFeatureLevel::Type FeatureLevel = World->Scene->GetFeatureLevel();
	FName TextureRenderTargetName = OutputRenderTarget->GetFName();
	//添加渲染指令
	ENQUEUE_RENDER_COMMAND(CaptureCommand)(
		[TextureRenderTargetResource, FeatureLevel, MyColor, TextureRenderTargetName](FRHICommandListImmediate& RHICmdList)
	{
		DrawTestShaderRenderTarget_RenderThread(RHICmdList, TextureRenderTargetResource, FeatureLevel, TextureRenderTargetName, MyColor);
	}
	);

}

#undef LOCTEXT_NAMESPACE  