// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "Rendering/CustomSceneViewExtension.h"
#include "CustomShaderSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TUT_2_CUSTOM_SHADERS_API UCustomShaderSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

private:
	TSharedPtr< class FCustomSceneViewExtension, ESPMode::ThreadSafe > CustomSceneViewExtension;
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
};
