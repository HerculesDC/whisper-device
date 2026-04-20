// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "UI/UILayerTypes.h"
#include "UWhisperCommonBaseWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class WHISPER_API UUWhisperCommonBaseWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
public:
    // Which layer this widget belongs to
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Layer")
    EUILayer AssignedLayer = EUILayer::Panel;

    // Override in subclasses to set which widget gets focus on activation
    virtual UWidget* NativeGetDesiredFocusTarget() const override;

    // Called by UIManager — triggers CommonUI's activation pipeline
    UFUNCTION(BlueprintCallable, Category = "UI")
    void RequestShow();

    // Called by UIManager — triggers deactivation
    UFUNCTION(BlueprintCallable, Category = "UI")
    void RequestHide();

protected:
    // CommonUI calls these when activation state changes
    virtual void NativeOnActivated() override;
    virtual void NativeOnDeactivated() override;

    // Override in Blueprint or C++ subclasses
    UFUNCTION(BlueprintNativeEvent, Category = "UI")
    void OnWidgetActivated();

    UFUNCTION(BlueprintNativeEvent, Category = "UI")
    void OnWidgetDeactivated();
};
