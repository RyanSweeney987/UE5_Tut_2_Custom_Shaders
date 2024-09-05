// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

namespace ComputePassBase
{
	static constexpr ETextureCreateFlags ComputeTextureCreationFlags = TexCreate_ShaderResource | TexCreate_UAV | TexCreate_FastVRAM | TexCreate_RenderTargetable;
}

/**
 * 
 */
struct UE5_TUT_2_CUSTOM_SHADERS_API FComputePassInputParams
{
	FRDGBuilder& GraphBuilder;
	const FGlobalShaderMap* GlobalShaderMap;
	FIntPoint ThreadCount;

	FComputePassInputParams(FRDGBuilder& InGraphBuilder, const FGlobalShaderMap* InGlobalShaderMap, FIntPoint InThreadCount)
		: GraphBuilder(InGraphBuilder)
		, GlobalShaderMap(InGlobalShaderMap)
		, ThreadCount(InThreadCount)
	{}
};

/**
 * 
 */
struct UE5_TUT_2_CUSTOM_SHADERS_API FComputePassOutputParams
{
	FRDGTextureRef Texture;
	
	FComputePassOutputParams(const FRDGTextureRef InTexture = nullptr)
		: Texture(InTexture)
	{}
};

/**
 * 
 */
class UE5_TUT_2_CUSTOM_SHADERS_API FComputePassBase
{
public:
	FComputePassBase() = default;
	virtual ~FComputePassBase() = default;

	virtual FComputePassOutputParams AddPass(FComputePassInputParams& InputParams) = 0;
};
