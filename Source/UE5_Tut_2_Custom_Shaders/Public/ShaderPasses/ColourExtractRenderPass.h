// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PostProcess/PostProcessInputs.h"
#include "RenderPasses/RenderPassBase.h"

// This can be included in your FGlobalShader class
// Handy to keep them separate as you can use the same Params for multiple shaders
BEGIN_SHADER_PARAMETER_STRUCT(FColourExtractParams,)
	// Make sure it's a float vector and not a double vector
	SHADER_PARAMETER(FVector3f, TargetColour)

	// Texture type is same as set in shader 
	SHADER_PARAMETER_RDG_TEXTURE(Texture2D, SceneColorTexture)

	// Only needed if we're outputting to a render target
	RENDER_TARGET_BINDING_SLOTS()
END_SHADER_PARAMETER_STRUCT()

class FColourExtractPS : public FGlobalShader
{
	DECLARE_EXPORTED_SHADER_TYPE(FColourExtractPS, Global, );
	using FParameters = FColourExtractParams;
	SHADER_USE_PARAMETER_STRUCT(FColourExtractPS, FGlobalShader);
};

/**
 * Override for making it easier to pass in the required parameters
 * Can override the FRenderPassOutputParams to return more than just a texture reference
 */
struct UE5_TUT_2_CUSTOM_SHADERS_API FColourExtractInputParams : public FRenderPassInputParams
{
	FIntRect Viewport;
	const FPostProcessingInputs& Inputs;
	
	FColourExtractInputParams(FRDGBuilder& InGraphBuilder, const FGlobalShaderMap* InGlobalShaderMap, const FIntRect& InViewport, const FPostProcessingInputs& InInputs)
		: FRenderPassInputParams(InGraphBuilder, InGlobalShaderMap), Viewport(InViewport), Inputs(InInputs)
	{}
};

/**
 * 
 */
class UE5_TUT_2_CUSTOM_SHADERS_API FColourExtractRenderPass : public FRenderPassBase
{
public:
	FColourExtractRenderPass() = default;

	virtual FRenderPassOutputParams AddPass(FRenderPassInputParams& InParams) override;
};
