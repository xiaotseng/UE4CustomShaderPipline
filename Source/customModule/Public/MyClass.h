// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyClass.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMMODULE_API UMyClass : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		static void readJson(FString filePath);
};
