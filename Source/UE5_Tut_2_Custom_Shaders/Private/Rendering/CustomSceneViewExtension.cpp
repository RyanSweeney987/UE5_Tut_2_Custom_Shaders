// Fill out your copyright notice in the Description page of Project Settings.


#include "Rendering/CustomSceneViewExtension.h"

#include "PixelShaderUtils.h"
#include "RenderGraphEvent.h"
#include "SceneRenderTargetParameters.h"
#include "SceneTexturesConfig.h"
#include "ShaderPasses/ColourExtractRenderPass.h"

DECLARE_GPU_DRAWCALL_STAT(ColourExtract); // Unreal Insights

FCustomSceneViewExtension::FCustomSceneViewExtension(const FAutoRegister& AutoRegister) : FSceneViewExtensionBase(AutoRegister)
{
}

void FCustomSceneViewExtension::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View,
                                                                const FPostProcessingInputs& Inputs)
{
	FSceneViewExtensionBase::PrePostProcessPass_RenderThread(GraphBuilder, View, Inputs);
	
	checkSlow(View.bIsViewInfo);
	const FIntRect Viewport = static_cast<const FViewInfo&>(View).ViewRect;
	// Requires RHI
	const FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);
	
	RDG_GPU_STAT_SCOPE(GraphBuilder, ColourExtract); // Unreal Insights
	RDG_EVENT_SCOPE(GraphBuilder,  "Colour Extract"); // RenderDoc
	
	// Without the helper function
	// This is to get the base colour without shading
	const FSceneTextureShaderParameters SceneTextures = CreateSceneTextureShaderParameters(GraphBuilder, View, ESceneTextureSetupMode::SceneColor | ESceneTextureSetupMode::GBuffers);
	// This is colour with shading and shadows
	const FScreenPassTexture SceneColourTexture((*Inputs.SceneTextures)->SceneColorTexture, Viewport);
	
	FColourExtractPS::FParameters* Parameters = GraphBuilder.AllocParameters<FColourExtractPS::FParameters>();
	Parameters->SceneColorTexture = SceneColourTexture.Texture;
	Parameters->SceneTextures = SceneTextures;
	// Convert the target colour to Lab colour space here instead of in the shader
	// That will reduce the amount of calculations needed in the shader
	Parameters->TargetColour = FVector3f(1.0f, 0.0f, 0.0f);
	Parameters->View = View.ViewUniformBuffer;
	// This will load the scene colour texture, and render to it
	Parameters->RenderTargets[0] = FRenderTargetBinding((*Inputs.SceneTextures)->SceneColorTexture, ERenderTargetLoadAction::ELoad);
	
	TShaderMapRef<FColourExtractPS> PixelShader(GlobalShaderMap);
	FPixelShaderUtils::AddFullscreenPass(GraphBuilder, GlobalShaderMap, FRDGEventName(TEXT("Colour Extract Pass")), PixelShader, Parameters, Viewport);
}

#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 5
void FCustomSceneViewExtension::SubscribeToPostProcessingPass(EPostProcessingPass PassId, const FSceneView& View, FAfterPassCallbackDelegateArray& InOutPassCallbacks, bool bIsPassEnabled)
#else
void FCustomSceneViewExtension::SubscribeToPostProcessingPass(EPostProcessingPass Pass,
	FAfterPassCallbackDelegateArray& InOutPassCallbacks, bool bIsPassEnabled)
#endif
{
	if(Pass == EPostProcessingPass::MotionBlur)
	{
#if false
		InOutPassCallbacks.Add(FAfterPassCallbackDelegate::CreateRaw(this, &FCustomSceneViewExtension::CustomPostProcessFunction));
#endif
	}
}

FScreenPassTexture FCustomSceneViewExtension::CustomPostProcessFunction(FRDGBuilder& GraphBuilder, const FSceneView& SceneView, const FPostProcessMaterialInputs& Inputs)
{
	// Do something here
	return FScreenPassTexture();
}
