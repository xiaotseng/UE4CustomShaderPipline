// Fill out your copyright notice in the Description page of Project Settings.
#include "MyClass.h"
#include "Engine.h"



void UMyClass::readJson(FString filePath)
{
	FString fileSource;
	bool jsonResult = FFileHelper::LoadFileToString(fileSource, *filePath);
	if (jsonResult)//加载成功
	{
		TSharedRef<FJsonStringReader> jsonReader=FJsonStringReader::Create(fileSource);
		TSharedPtr<FJsonObject> jObject = MakeShareable(new FJsonObject());
		jsonResult=FJsonSerializer::Deserialize<TCHAR>(jsonReader, jObject);
		if (jsonResult)
		{
			const TArray<TSharedPtr<FJsonValue>> &Persons = jObject->GetArrayField(TEXT("Persons"));
			for (int i = 0; i < Persons.Num(); ++i)
			{
				const TSharedPtr<FJsonObject> &person = Persons[i]->AsObject();
				FString name = person->GetStringField(TEXT("name"));
				int age = int(person->GetNumberField(TEXT("age")));
				if (GEngine)
				{
					UE_LOG(LogClass, Log, TEXT("姓名：%s........年龄：%d"), *name, age);
				}
			}
		}
		else
		{
			if (GEngine)
			{
				UE_LOG(LogClass, Log, TEXT("解析json错误"));
			}
		}
	}
	else//加载失败
	{
		if (GEngine)
		{
			UE_LOG(LogClass, Log, TEXT("读取文件失败"));
		}
	}
}
