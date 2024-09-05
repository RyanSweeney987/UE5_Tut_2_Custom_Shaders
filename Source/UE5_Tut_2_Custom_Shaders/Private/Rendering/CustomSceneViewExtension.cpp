// Fill out your copyright notice in the Description page of Project Settings.


#include "Rendering/CustomSceneViewExtension.h"

#include "RenderGraphEvent.h"
#include "ShaderPasses/ColourExtractRenderPass.h"

DECLARE_GPU_DRAWCALL_STAT(ColourExtract);

FCustomSceneViewExtension::FCustomSceneViewExtension(const FAutoRegister& AutoRegister) : FSceneViewExtensionBase(AutoRegister)
{
}

void FCustomSceneViewExtension::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View,
	const FPostProcessingInputs& Inputs)
{
	FSceneViewExtensionBase::PrePostProcessPass_RenderThread(GraphBuilder, View, Inputs);

	checkSlow(View.bIsViewInfo);
	const FIntRect Viewport = static_cast<const FViewInfo&>(View).ViewRect;
	const FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);
	
	RDG_GPU_STAT_SCOPE(GraphBuilder, ColourExtract);
	RDG_EVENT_SCOPE(GraphBuilder,  "Colour Extract");

	FColourExtractInputParams InputParams(GraphBuilder, GlobalShaderMap, Viewport, Inputs);
	FColourExtractRenderPass().AddPass(InputParams);
}
