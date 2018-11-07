#pragma once
#include "Public/GlobalShader.h"  
//顶点布局
class FVertexLayoutBake:public FRenderResource
{
public:
	FVertexDeclarationRHIRef VertexDeclarationRHI;
	virtual void InitRHI() override;
	virtual void ReleaseRHI() override;
};

//基类
class FBakeShader :public FGlobalShader
{
public:
	FBakeShader() {}
	FBakeShader(const ShaderMetaType::CompiledShaderInitializerType &Initializer);
	static bool ShouldCache(EShaderPlatform Platform);//是否要缓存编译代码
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);//是否要排序
	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, 
																					FShaderCompilerEnvironment& OutEnvironment);//修改编译环境
};
//顶点着色器Shader类
class FBakeShaderVS :public FBakeShader
{
	DECLARE_SHADER_TYPE(FBakeShaderVS, Global)
public:
	FBakeShaderVS() {}
	FBakeShaderVS(const ShaderMetaType::CompiledShaderInitializerType &Initializer) :FBakeShader(Initializer) {
	}
};
//像素着色器Shader类
class FBakeShaderPS :public FBakeShader
{
	DECLARE_SHADER_TYPE(FBakeShaderPS, Global)
public:
	FBakeShaderPS() {}
	FBakeShaderPS(const ShaderMetaType::CompiledShaderInitializerType &Initializer) :FBakeShader(Initializer) {
	}
};