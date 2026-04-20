// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "UI/UILayerTypes.h"
#include "UUIManager.generated.h"

/**
 * 
 */

class UWhisperCommonBaseWidget;
class UCommonActivatableWidgetStack;

UCLASS(BlueprintType)
class WHISPER_API UUIManager : public UObject
{
	GENERATED_BODY()
	
public:
    void Initialize(APlayerController* InPlayerController, UUserWidget* InRootWidget);

    // Push a widget onto a layer's stack (creates it if not cached)
    UFUNCTION(BlueprintCallable, Category = "UI")
    UWhisperCommonBaseWidget* PushWidget(TSubclassOf<UWhisperCommonBaseWidget> WidgetClass, EUILayer Layer);

    // Pop the top widget from a layer
    UFUNCTION(BlueprintCallable, Category = "UI")
    void PopWidget(EUILayer Layer);

    // Pop ALL widgets from a layer
    UFUNCTION(BlueprintCallable, Category = "UI")
    void ClearLayer(EUILayer Layer);

    // Get the currently active widget on a layer
    UFUNCTION(BlueprintCallable, Category = "UI")
    UWhisperCommonBaseWidget* GetActiveWidget(EUILayer Layer) const;

    UFUNCTION(BlueprintPure, Category = "UI")
    bool IsModalOpen() const;

    // Show a widget by its gameplay tag (e.g. "UI.Panel.QuestLog")
    UFUNCTION(BlueprintCallable, Category = "UI")
    UWhisperCommonBaseWidget* ShowWidgetByTag(FGameplayTag Tag);

    UFUNCTION(BlueprintCallable, Category = "UI")
    void HideWidgetByTag(FGameplayTag Tag);

private:
    // Tag → widget instance, built from the registry at init
    UPROPERTY()
    TMap<FGameplayTag, UWhisperCommonBaseWidget*> TaggedWidgets;

    void PreloadRegisteredWidgets();

    UPROPERTY()
    APlayerController* PlayerController;

    // One stack widget per layer, added to viewport at initialization
    UPROPERTY()
    TMap<EUILayer, UCommonActivatableWidgetStack*> LayerStacks;

    UPROPERTY()
    TMap<TSubclassOf<UWhisperCommonBaseWidget>, UWhisperCommonBaseWidget*> WidgetCache;

    UCommonActivatableWidgetStack* GetOrCreateStack(EUILayer Layer);
    UWhisperCommonBaseWidget* GetOrCreateWidget(TSubclassOf<UWhisperCommonBaseWidget> WidgetClass);

};
