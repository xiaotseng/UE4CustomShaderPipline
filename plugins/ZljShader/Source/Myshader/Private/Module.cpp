// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Module.h"

#define LOCTEXT_NAMESPACE "FMyshaderModule"

void FMyshaderModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FMyshaderModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyshaderModule, Myshader)
EXTERN_C DLLEXPORT  const char* myname="kele";
DLLEXPORT  int add(int a, int b) { return a + b; };