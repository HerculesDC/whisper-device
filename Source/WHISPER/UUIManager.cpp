// Fill out your copyright notice in the Description page of Project Settings.


#include "UUIManager.h"

#include "CommonBaseWidget.h"
#include "Widgets/CommonActivatableWidgetStack.h"
#include "WhisperWidgetRegistry.h"
#include "Blueprint/UserWidget.h"

void UUIManager::Initialize(APlayerController* InPlayerController, UUserWidget* InRootWidget)
{
    PlayerController = InPlayerController;

    for (EUILayer Layer : { EUILayer::Background, EUILayer::HUD,
        EUILayer::Panel, EUILayer::Overlay, EUILayer::Modal })
        GetOrCreateStack(Layer);

    // Read the registry and pre-create flagged widgets
    PreloadRegisteredWidgets();
}

UWhisperCommonBaseWidget* UUIManager::PushWidget(TSubclassOf<UWhisperCommonBaseWidget> WidgetClass, EUILayer Layer)
{
    if (!WidgetClass || !PlayerController) return nullptr;

    UCommonActivatableWidgetStack* Stack = GetOrCreateStack(Layer);
    if (!Stack) return nullptr;

    UWhisperCommonBaseWidget* Widget = GetOrCreateWidget(WidgetClass);
    if (!Widget) return nullptr;

    // PushWidget is CommonUI's API — it adds the widget to the
    // stack and calls ActivateWidget() internally
    Stack->AddWidget(Widget->GetClass());
    return Widget;
}

void UUIManager::PopWidget(EUILayer Layer)
{
    if (UCommonActivatableWidgetStack* Stack = LayerStacks.FindRef(Layer))
        Stack->RemoveWidget(*Stack->GetActiveWidget());
}

void UUIManager::ClearLayer(EUILayer Layer)
{
    if (UCommonActivatableWidgetStack* Stack = LayerStacks.FindRef(Layer))
    {
        while (Stack->GetNumWidgets() > 0)
            Stack->RemoveWidget(*Stack->GetActiveWidget());
    }
}

UWhisperCommonBaseWidget* UUIManager::GetActiveWidget(EUILayer Layer) const
{
    if (UCommonActivatableWidgetStack* Stack = LayerStacks.FindRef(Layer))
        return Cast<UWhisperCommonBaseWidget>(Stack->GetActiveWidget());
    return nullptr;
}

bool UUIManager::IsModalOpen() const
{
    UCommonActivatableWidgetStack* Stack = LayerStacks.FindRef(EUILayer::Modal);
    return Stack && Stack->GetNumWidgets() > 0;
}

UCommonActivatableWidgetStack* UUIManager::GetOrCreateStack(EUILayer Layer)
{
    if (UCommonActivatableWidgetStack** Found = LayerStacks.Find(Layer))
        return *Found;

    UCommonActivatableWidgetStack* Stack =
        CreateWidget<UCommonActivatableWidgetStack>(PlayerController,
            UCommonActivatableWidgetStack::StaticClass());

    if (Stack)
    {
        Stack->AddToViewport((int32)Layer); // Z-order = layer value
        LayerStacks.Add(Layer, Stack);
    }
    return Stack;
}

UWhisperCommonBaseWidget* UUIManager::GetOrCreateWidget(TSubclassOf<UWhisperCommonBaseWidget> WidgetClass)
{
    if (UWhisperCommonBaseWidget** Found = WidgetCache.Find(WidgetClass))
        return *Found;

    UWhisperCommonBaseWidget* Widget = CreateWidget<UWhisperCommonBaseWidget>(PlayerController, WidgetClass);
    if (Widget)
        WidgetCache.Add(WidgetClass, Widget);
    return Widget;
}

void UUIManager::PreloadRegisteredWidgets()
{
    const UWhisperWidgetRegistry* Registry = UWhisperWidgetRegistry::Get();
    if (!Registry) return;

    for (const FUIWidgetEntry& Entry : Registry->RegisteredWidgets)
    {
        if (!Entry.bPreload || !Entry.WidgetTag.IsValid()) continue;

        // Resolve the soft class pointer synchronously at startup
        TSubclassOf<UWhisperCommonBaseWidget> ResolvedClass =
            Entry.WidgetClass.LoadSynchronous();

        if (!ResolvedClass) continue;

        UWhisperCommonBaseWidget* Widget =
            CreateWidget<UWhisperCommonBaseWidget>(PlayerController, ResolvedClass);

        if (Widget)
        {
            // Add it to the right layer's stack (hidden/deactivated)
            UCommonActivatableWidgetStack* Stack = GetOrCreateStack(Entry.Layer);
            if (Stack) Stack->AddWidget(ResolvedClass);

            TaggedWidgets.Add(Entry.WidgetTag, Widget);
        }
    }
}

UWhisperCommonBaseWidget* UUIManager::ShowWidgetByTag(FGameplayTag Tag)
{
    if (UWhisperCommonBaseWidget** Found = TaggedWidgets.Find(Tag))
    {
        (*Found)->ActivateWidget();
        return *Found;
    }

    UE_LOG(LogTemp, Warning,
        TEXT("UIManager: no widget registered for tag %s"), *Tag.ToString());
    return nullptr;
}

void UUIManager::HideWidgetByTag(FGameplayTag Tag)
{
    if (UWhisperCommonBaseWidget** Found = TaggedWidgets.Find(Tag))
        (*Found)->DeactivateWidget();
}