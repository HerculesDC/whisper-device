// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WhisperDevice.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class WHISPER_API WhisperDevice : public UUserWidget
{
	GENERATED_BODY()
public:
	WhisperDevice();
	~WhisperDevice();
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};
