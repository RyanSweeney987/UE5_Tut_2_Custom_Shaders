// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CoreMinimal.h"
#include "PixelShaderUtils.h"

namespace RenderPassBase
{
	static constexpr ETextureCreateFlags RenderTextureCreationFlags = TexCreate_ShaderResource | TexCreate_UAV | TexCreate_FastVRAM | TexCreate_RenderTargetable;
}

/**
 * 
 */
struct UE5_TUT_2_CUSTOM_SHADERS_API FRenderPassInputParams
{
	FRDGBuilder& GraphBuilder;
	const FGlobalShaderMap* GlobalShaderMap;

	FRenderPassInputParams(FRDGBuilder& InGraphBuilder, const FGlobalShaderMap* InGlobalShaderMap)
		: GraphBuilder(InGraphBuilder)
		, GlobalShaderMap(InGlobalShaderMap)
	{}
};

/**
 * 
 */
struct UE5_TUT_2_CUSTOM_SHADERS_API FRenderPassOutputParams
{
	FRDGTextureRef Texture;
	
	FRenderPassOutputParams(const FRDGTextureRef InTexture = nullptr)
		: Texture(InTexture)
	{}
};

/**
 * 
 */
class UE5_TUT_2_CUSTOM_SHADERS_API FRenderPassBase
{
protected:
	bool bNeverCull = false;
	bool bEnableCompute = false;
	bool bEnableAsyncCompute = false;

	FRenderPassBase() = default;
	virtual ~FRenderPassBase() = default;
public:
	virtual FRenderPassOutputParams AddPass(FRenderPassInputParams& InParams) = 0;
protected:
	template<typename TShaderClass>
	void AddRenderPass(FRDGBuilder& GraphBuilder,
		const FGlobalShaderMap* GlobalShaderMap,
		FRDGEventName&& PassName,
		typename TShaderClass::FParameters* Parameters,
		const FIntRect& Viewport,
		FRHIBlendState* BlendState = nullptr,
		FRHIRasterizerState* RasterizerState = nullptr,
		FRHIDepthStencilState* DepthStencilState = nullptr,
		uint32 StencilRef = 0)
	{
		const TShaderRef<TShaderClass> PixelShader = TShaderMapRef<TShaderClass>(GlobalShaderMap);
	
		check(PixelShader.IsValid());
		ClearUnusedGraphResources(PixelShader, Parameters);
	
		ERDGPassFlags PassFlags = ERDGPassFlags::Raster | (bNeverCull ? ERDGPassFlags::NeverCull : ERDGPassFlags::None);
		
		GraphBuilder.AddPass(
			Forward<FRDGEventName>(PassName),
			Parameters,
			PassFlags,
			[Parameters, GlobalShaderMap, PixelShader, Viewport, BlendState, RasterizerState, DepthStencilState, StencilRef](FRHICommandList& RHICmdList)
		{
			FPixelShaderUtils::DrawFullscreenPixelShader(RHICmdList, GlobalShaderMap, PixelShader, *Parameters, Viewport, 
				BlendState, RasterizerState, DepthStencilState, StencilRef);
		});
	}
};
