// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomShaderSubsystem.h"

#include "SceneViewExtension.h"

void UCustomShaderSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	CustomSceneViewExtension = FSceneViewExtensions::NewExtension<FCustomSceneViewExtension>();
}

void UCustomShaderSubsystem::Deinitialize()
{
	Super::Deinitialize();

	CustomSceneViewExtension.Reset();
	CustomSceneViewExtension = nullptr;
}
