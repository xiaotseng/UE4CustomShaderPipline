// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyReflectionActor.generated.h"
class USoundWaveProcedural;
UCLASS()
class CUSTOMSHADERPIPLINE_API AMyReflectionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyReflectionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int fefe;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USoundWaveProcedural* SoundStreaming;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<FString> properties;
	UFUNCTION(BlueprintCallable)
		void setName();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
