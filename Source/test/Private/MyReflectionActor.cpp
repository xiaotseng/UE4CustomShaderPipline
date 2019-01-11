// Fill out your copyright notice in the Description page of Project Settings.

#include "MyReflectionActor.h"
#include "Engine/Engine.h"
#include "Runtime/Engine/Classes/Sound/SoundWaveProcedural.h"


// Sets default values
AMyReflectionActor::AMyReflectionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SoundStreaming = NewObject<USoundWaveProcedural>();
	fefe = 42;
	

}

// Called when the game starts or when spawned
void AMyReflectionActor::BeginPlay()
{
	Super::BeginPlay();
	//GEngine->AddOnScreenDebugMessage(0, 10, FColor::Blue, SoundStreaming->GetName(), true);
	
	
}

void AMyReflectionActor::setName()
{
	
	UProperty* currentProperty = this->GetClass()->PropertyLink;
	while (currentProperty != NULL)
	{
		properties.Add(currentProperty->GetMetaData("Category"));
		
		//GEngine->AddOnScreenDebugMessage(0, 10, FColor::Blue, pN, true);
		currentProperty = currentProperty->PropertyLinkNext;
	}
	//通过名字找到属性
	UProperty* pp = this->GetClass()->FindPropertyByName(FName("name"));
	if (!pp == NULL)
	{
		int offset=pp->GetOffset_ReplaceWith_ContainerPtrToValuePtr();
		int value = 233;
		pp->CopyCompleteValue(((int32*)(((char*)this) + offset)), &value);
		//*((int32*)(((char*)this) + offset)) = 12;
	}
}

// Called every frame
void AMyReflectionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

