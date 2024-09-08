﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataDrivenShaderPlatformInfo.h"
#include "SceneTexturesConfig.h"
#include "PostProcess/PostProcessInputs.h"
// Delete this if you don't have the UE5ShaderUtils plugin
#include "RenderPasses/RenderPassBase.h"

// This can be included in your FGlobalShader class
// Handy to keep them separate as you can use the same Params for multiple shaders
BEGIN_SHADER_PARAMETER_STRUCT(FColourExtractParams,)
	// Make sure it's a float vector and not a double vector
	SHADER_PARAMETER(FVector3f, TargetColour)

	// Texture type is same as set in shader 
	SHADER_PARAMETER_RDG_TEXTURE(Texture2D, SceneColorTexture)
	SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, View)
	SHADER_PARAMETER_STRUCT_INCLUDE(FSceneTextureShaderParameters, SceneTextures)

	// Only needed if we're outputting to a render target
	RENDER_TARGET_BINDING_SLOTS()
END_SHADER_PARAMETER_STRUCT()

class FColourExtractPS : public FGlobalShader
{
	DECLARE_EXPORTED_SHADER_TYPE(FColourExtractPS, Global, );
	using FParameters = FColourExtractParams;
	SHADER_USE_PARAMETER_STRUCT(FColourExtractPS, FGlobalShader);

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
	}
	
	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);

		// When changing this, you may need to change something in the shader for it to take effect
		// A simple comment with a bit of gibberish seems to be enough
		SET_SHADER_DEFINE(OutEnvironment, USE_UNLIT_SCENE_COLOUR, 0);
	}
};

/**
 * Override for making it easier to pass in the required parameters
 * Can override the FRenderPassOutputParams to return more than just a texture reference
 *
 * Delete this struct if you don't have the UE5ShaderUtils plugin
 */
struct UE5_TUT_2_CUSTOM_SHADERS_API FColourExtractInputParams : public FRenderPassInputParams
{
	FIntRect Viewport;
	const FPostProcessingInputs& Inputs;
	const FSceneView& View;
	
	FColourExtractInputParams(FRDGBuilder& InGraphBuilder, const FGlobalShaderMap* InGlobalShaderMap, const FIntRect& InViewport, const FPostProcessingInputs& InInputs,  const FSceneView& InView)
		: FRenderPassInputParams(InGraphBuilder, InGlobalShaderMap), Viewport(InViewport), Inputs(InInputs), View(InView)
	{}
};

/**
 * Delete this class if you don't have the UE5ShaderUtils plugin
 */
class UE5_TUT_2_CUSTOM_SHADERS_API FColourExtractRenderPass : public FRenderPassBase
{
public:
	FColourExtractRenderPass() = default;

	virtual FRenderPassOutputParams AddPass(FRenderPassInputParams& InParams) override;
};