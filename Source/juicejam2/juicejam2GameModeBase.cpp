// Copyright Epic Games, Inc. All Rights Reserved.


#include "juicejam2GameModeBase.h"

#include "JsonObjectConverter.h"
#include "Kismet/KismetSystemLibrary.h"

Ajuicejam2GameModeBase::Ajuicejam2GameModeBase()
{
	InitializeMessageConstants();	
}

void Ajuicejam2GameModeBase::BeginPlay()
{
	if(TerminalUIWidgetClass)
	{
		UTerminalUIWidget* TerminalUIWidget = CreateWidget<UTerminalUIWidget>(GetWorld(), TerminalUIWidgetClass);
		
		if(TerminalUIWidget)
		{
			TerminalUIWidget->AddToViewport();

			if(MessageConstants.Messages.Num() > 0)
			{
				TerminalUIWidget->AddMessage(FText::FromString(MessageConstants.Messages[0]));
			}
		}
	}
}

void Ajuicejam2GameModeBase::InitializeMessageConstants()
{
	bool bOutSuccess = false;
	FString OutInfoMessage = "";

	FString ContentDir = UKismetSystemLibrary::GetProjectContentDirectory();

	FString Path = FString::Format(TEXT("{0}/Config/MessageConstants.json"), {ContentDir});
	
	TSharedPtr<FJsonObject> JsonObject = ReadJson(Path, bOutSuccess, OutInfoMessage);
	
	if(bOutSuccess)
	{
		FMessageConstants Messages;
		
		FJsonObjectConverter::JsonObjectToUStruct<FMessageConstants>(JsonObject.ToSharedRef(), &Messages);

		MessageConstants = Messages;
	}

	UE_LOG(LogTemp, Warning, TEXT("%s"), *OutInfoMessage);
}

FString Ajuicejam2GameModeBase::ReadStringFromFile(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage)
{
	if(!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Read String From File Failed - File doesn't exist - '%s'"), *FilePath);
		return "";
	}

	FString RetString = "";

	if(!FFileHelper::LoadFileToString(RetString, *FilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Read String From File Failed - Was not able to read the file. - '%s'"), *FilePath);
		return "";
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Read String From File Succeeded - '%s'"), *FilePath);
	return RetString;
}

TSharedPtr<FJsonObject> Ajuicejam2GameModeBase::ReadJson(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage)
{
	FString JsonString = ReadStringFromFile(JsonFilePath, bOutSuccess, OutInfoMessage);

	if(!bOutSuccess)
	{
		return nullptr;
	}

	TSharedPtr<FJsonObject> RetJsonObject;

	if(!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), RetJsonObject))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Read Message Constants JSON Failed - Was not able to deserialize the JSON. - '%s'"), *JsonFilePath);
		return nullptr;
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Read Message Constants JSON Succeeded - '%s'"), *JsonFilePath);
	return RetJsonObject;
}
