// Fill out your copyright notice in the Description page of Project Settings.

#include "ZljSlate.h"
#include "Engine/Engine.h"


// Sets default values
AZljSlate::AZljSlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyStruct.Actor = this;
	MyStruct.Name = "dsds";
	MyStruct.Number = 500;

	
	for (TFieldIterator<UProperty> PropIt(GetClass()); PropIt; ++PropIt)
	{
		UProperty* ppt = *PropIt;
		Properties.Push(*PropIt);
	}

	

	


}


void AZljSlate::showUI()
{
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Blue, TEXT("Struct Value is: "),true,FVector2D::UnitVector);
	UWorld* world=GEngine->GetWorld();
	AWorldSettings* settings=world->GetWorldSettings();



}

// Called when the game starts or when spawned
void AZljSlate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZljSlate::Tick(float DeltaTime)
{ 
	Super::Tick(DeltaTime);

}

