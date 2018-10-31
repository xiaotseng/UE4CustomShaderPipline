// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "Engine.h"

void AMyHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SAssignNew(MainUI, SFrontPage).OnwerHUD(this);
	if (GEngine->IsValidLowLevel())
	{
		GEngine->GameViewport->AddViewportWidgetContent(MainUI.ToSharedRef());
	}
	
}
