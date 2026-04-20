// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WhisperHUD.generated.h"

/**
 * 
 */
UCLASS()
class WHISPER_API AWhisperHUD : public AHUD
{
	GENERATED_BODY()
public:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintPure, Category = "UI")
    UUIManager* GetUIManager() const { return UIManager; }

private:
    UPROPERTY()
    UUIManager* UIManager;

    // The root layout widget that holds the layer stacks
    UPROPERTY()
    UUserWidget* RootLayout;

    // Set this in Blueprint subclass or GameMode CDO
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> RootLayoutClass;
};
