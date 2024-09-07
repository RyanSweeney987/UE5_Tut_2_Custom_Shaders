// Fill out your copyright notice in the Description page of Project Settings.

#include "ShaderPasses/ColourExtractRenderPass.h"

#include "SceneRenderTargetParameters.h"
#include "SceneTexturesConfig.h"

// The location is set as VirtualMappingSetInModuleInitialise/private/NameOfShader.usf
// MainPS is the entry point for the pixel shader - You can have multiple in a file but you have to specify separately
IMPLEMENT_SHADER_TYPE(, FColourExtractPS, TEXT("/CustomShaders/private/TutorialShader.usf"), TEXT("MainPS"), SF_Pixel);

FRenderPassOutputParams FColourExtractRenderPass::AddPass(FRenderPassInputParams& InParams)
{
	// Cast the input params to the correct type to get access to all the values
	const FColourExtractInputParams& Params = static_cast<FColourExtractInputParams&>(InParams);

	const FSceneTextureShaderParameters SceneTextures = CreateSceneTextureShaderParameters(Params.GraphBuilder, Params.View, ESceneTextureSetupMode::SceneColor | ESceneTextureSetupMode::GBuffers);
	
	const FScreenPassTexture SceneColourTexture((*Params.Inputs.SceneTextures)->SceneColorTexture, Params.Viewport);

	FColourExtractPS::FParameters* Parameters = Params.GraphBuilder.AllocParameters<FColourExtractPS::FParameters>();
	Parameters->SceneColorTexture = SceneColourTexture.Texture;
	Parameters->SceneTextures = SceneTextures;
	// Convert the target colour to Lab colour space here instead of in the shader
	// That will reduce the amount of calculations needed in the shader
	Parameters->TargetColour = FVector3f(0.0f, 1.0f, 0.0f);
	Parameters->View = Params.View.ViewUniformBuffer;
	// This will load the scene colour texture, and render to it
	Parameters->RenderTargets[0] = FRenderTargetBinding((*Params.Inputs.SceneTextures)->SceneColorTexture, ERenderTargetLoadAction::ELoad);
	
	// My method that allows for more control and customisation
	AddRenderPass<FColourExtractPS>(Params.GraphBuilder, Params.GlobalShaderMap, FRDGEventName(TEXT("Colour Extract Pass")), Parameters, Params.Viewport);

	// Return the output params - default a nullptr texture ref
	return FRenderPassOutputParams();
}