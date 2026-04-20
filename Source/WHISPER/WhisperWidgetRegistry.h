// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UI/UILayerTypes.h"
#include "WhisperWidgetRegistry.generated.h"

USTRUCT(BlueprintType)
struct FUIWidgetEntry
{
    GENERATED_BODY()

    // The Blueprint (or C++) class to instantiate
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget")
    TSoftClassPtr<class UCommonBaseWidget> WidgetClass;

    // Friendly tag used to show/hide it — e.g. "QuestLog", "Map"
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget")
    FGameplayTag WidgetTag;

    // Which layer it lives on
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget")
    EUILayer Layer = EUILayer::Panel;

    // If true, UIManager pre-creates this widget at startup
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget")
    bool bPreload = true;
};

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "UI Widget Registry"))
class WHISPER_API UWhisperWidgetRegistry : public UDeveloperSettings
{
	GENERATED_BODY()
public:
    UWhisperWidgetRegistry()
    {
        CategoryName = TEXT("Game");
        SectionName = TEXT("UI Widget Registry");
    }

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Widgets",
        meta = (TitleProperty = "WidgetTag"))
    TArray<FUIWidgetEntry> RegisteredWidgets;

    // Convenience accessor — no need to find the CDO manually
    static const UWhisperWidgetRegistry* Get()
    {
        return GetDefault<UWhisperWidgetRegistry>();
    }
};
