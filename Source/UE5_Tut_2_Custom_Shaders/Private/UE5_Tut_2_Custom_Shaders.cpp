// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5_Tut_2_Custom_Shaders.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FUE5_Tut_2_Custom_ShadersModule"

void FUE5_Tut_2_Custom_ShadersModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Shaders is the folder with a private folder inside
	const FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("UE5_Tut_2_Custom_Shaders"))->GetBaseDir(), TEXT("Shaders"));
	if(!AllShaderSourceDirectoryMappings().Contains(TEXT("/CustomShaders")))
	{
		AddShaderSourceDirectoryMapping(TEXT("/CustomShaders"), PluginShaderDir);
	}
}

void FUE5_Tut_2_Custom_ShadersModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUE5_Tut_2_Custom_ShadersModule, UE5_Tut_2_Custom_Shaders)