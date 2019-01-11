#include "MyBakeShader.h"

#include "Engine.h"

FBakeShader::FBakeShader(const ShaderMetaType::CompiledShaderInitializerType &Initializer) :FGlobalShader(Initializer)
{
	//Initializer.ParameterMap.
}

bool FBakeShader::ShouldCache(EShaderPlatform Platform)
{
	return true;
}

bool FBakeShader::ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
{
	//return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM4);  
	return true;
}

void FBakeShader::ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
{
	FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
	OutEnvironment.SetDefine(TEXT("TEST_MICRO"), 1);
}
//实现
IMPLEMENT_SHADER_TYPE(, FBakeShaderVS, TEXT("/Plugin/ZljShader/Private/MyBakeShader.usf"), TEXT("MainVS"), SF_Vertex)
IMPLEMENT_SHADER_TYPE(, FBakeShaderPS, TEXT("/Plugin/ZljShader/Private/MyBakeShader.usf"), TEXT("MainPS"), SF_Pixel)

//实现渲染资源



void FVertexLayoutBake::InitRHI()
{
	FVertexDeclarationElementList ElementList;
	ElementList.Add(FVertexElement(0, STRUCT_OFFSET(ZLJ::MyVertex, Position), VET_Float3, 0, sizeof(ZLJ::MyVertex)));
	ElementList.Add(FVertexElement(0, STRUCT_OFFSET(ZLJ::MyVertex, VertexColor), VET_Float3, 1, sizeof(ZLJ::MyVertex)));
	ElementList.Add(FVertexElement(0, STRUCT_OFFSET(ZLJ::MyVertex, Normal), VET_Float3, 2, sizeof(ZLJ::MyVertex)));
	ElementList.Add(FVertexElement(0, STRUCT_OFFSET(ZLJ::MyVertex, Uv1), VET_Float2, 3, sizeof(ZLJ::MyVertex)));
	ElementList.Add(FVertexElement(0, STRUCT_OFFSET(ZLJ::MyVertex, Uv2), VET_Float2, 4, sizeof(ZLJ::MyVertex)));
	VertexDeclarationRHI = RHICreateVertexDeclaration(ElementList);
}

void FVertexLayoutBake::ReleaseRHI()
{
	VertexDeclarationRHI->Release();
}

