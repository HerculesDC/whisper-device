// Fill out your copyright notice in the Description page of Project Settings.


#include "UWhisperCommonBaseWidget.h"

UWidget* UUWhisperCommonBaseWidget::NativeGetDesiredFocusTarget() const
{
    // Default: return the widget itself. Subclasses override to
    // focus a specific button or list item on open.
    return const_cast<UUWhisperCommonBaseWidget*>(this);
}

void UUWhisperCommonBaseWidget::RequestShow()
{
    ActivateWidget(); // CommonUI built-in — triggers NativeOnActivated
}

void UUWhisperCommonBaseWidget::RequestHide()
{
    DeactivateWidget(); // CommonUI built-in — triggers NativeOnDeactivated
}

void UUWhisperCommonBaseWidget::NativeOnActivated()
{
    Super::NativeOnActivated();
    SetVisibility(ESlateVisibility::SelfHitTestInvisible);
    OnWidgetActivated();
}

void UUWhisperCommonBaseWidget::NativeOnDeactivated()
{
    Super::NativeOnDeactivated();
    SetVisibility(ESlateVisibility::Collapsed);
    OnWidgetDeactivated();
}

void UUWhisperCommonBaseWidget::OnWidgetActivated_Implementation() {}
void UUWhisperCommonBaseWidget::OnWidgetDeactivated_Implementation() {}