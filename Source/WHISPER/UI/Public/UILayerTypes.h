// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class UILayerTypes: uint8
{
	Background = 0,
	HUD = 10,
	Panel = 20,
	Overlay = 30,
	Modal = 40
};
