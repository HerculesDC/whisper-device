// Fill out your copyright notice in the Description page of Project Settings.


#include "WhisperHUD.h"

void AWhisperHUD::BeginPlay()
{
    Super::BeginPlay();

    if (RootLayoutClass)
    {
        RootLayout = CreateWidget<UUserWidget>(GetOwningPlayerController(), RootLayoutClass);
        RootLayout->AddToViewport(0);
    }

    UIManager = NewObject<UUIManager>(this);
    UIManager->Initialize(GetOwningPlayerController(), RootLayout);
}