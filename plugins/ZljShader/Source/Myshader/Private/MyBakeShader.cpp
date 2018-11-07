#include "MyBakeShader.h"

#include "Engine.h"

FBakeShader::FBakeShader(const ShaderMetaType::CompiledShaderInitializerType &Initializer) :FGlobalShader(Initializer)
{

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
	ElementList.Add(FVertexElement(0, 0, VET_Float4, 0, 24));
	ElementList.Add(FVertexElement(0, 16, VET_Float2, 1, 24));
	VertexDeclarationRHI = RHICreateVertexDeclaration(ElementList);
}

void FVertexLayoutBake::ReleaseRHI()
{
	VertexDeclarationRHI->Release();
}

