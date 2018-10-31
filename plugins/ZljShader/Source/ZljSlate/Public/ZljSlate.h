// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZljSlate.generated.h"

USTRUCT(BlueprintType)
struct ZLJSLATE_API FAaaa
{
	GENERATED_BODY()

		// 用UPROPERTY包裹，可以更方便的在蓝图中使用
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mantra")
		FString Name;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mantra")
		int32 Number;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mantra")
		AActor* Actor;
};


UCLASS()
class ZLJSLATE_API AZljSlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	
	AZljSlate();


	UFUNCTION(BlueprintCallable, Category = "Mantra")
		void showUI();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mantra")
	FAaaa MyStruct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mantra")
	TMap<AActor*,int> actor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mantra")
     AActor* fefe;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mantra")
	TArray<UProperty*> Properties;

	
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
