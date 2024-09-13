// Fill out your copyright notice in the Description page of Project Settings.

#include "ShaderPasses/ColourExtractRenderPass.h"

#include "SceneRenderTargetParameters.h"
#include "SceneTexturesConfig.h"

// The location is set as VirtualMappingSetInModuleInitialise/private/NameOfShader.usf
// MainPS is the entry point for the pixel shader - You can have multiple in a file but you have to specify separately
IMPLEMENT_SHADER_TYPE(, FColourExtractPS, TEXT("/CustomShaders/private/TutorialShader.usf"), TEXT("MainPS"), SF_Pixel);