// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SDDFileTree.h"
#include "FrontPage.h"
#include "MyHUD.generated.h"

/**
 * 
 */ 
UCLASS(Blueprintable)
class ZLJSLATE_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	virtual  void PostInitializeComponents() override;
	TSharedPtr<class SWidget> MainUI;
	//TSharedRef<class SWidget> dfdf;
	

	
	
};
