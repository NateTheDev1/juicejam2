// Copyright Epic Games, Inc. All Rights Reserved.


#include "juicejam2GameModeBase.h"

#include "JsonObjectConverter.h"
#include "Kismet/KismetSystemLibrary.h"

Ajuicejam2GameModeBase::Ajuicejam2GameModeBase()
{
	InitializeMessageConstants();	
}

void Ajuicejam2GameModeBase::OnResponse(int32 InstanceID, FString Response)
{
	FMessageConstantMessage Message = MessageConstants.Messages[InstanceID];

	if(Message.RightResponse == "")
	{
		return;
	}
		
	if(Message.RightResponse == Response)
	{
		if(StateHUD)
		{
			StateHUD->SetElectricityLevel(StateHUD->ElectricityLevel - 0.05f);
		}		
	} else
	{
		StateHUD->SetEmpathyLevel(StateHUD->EmpathyLevel - Message.EmpathyHit);
	}
}

void Ajuicejam2GameModeBase::OnPromptEnd(int32 InstanceID)
{
	UE_LOG(LogTemp, Warning, TEXT("OnPromptEnd: %d"), InstanceID);
	
	if(MessageConstants.Messages.Num() > CurrentMessageIndex)
	{
		if(TerminalUIWidget)
		{
			TerminalUIWidget->AddMessage(FText::FromString(MessageConstants.Messages[CurrentMessageIndex].Message), true, CurrentMessageIndex, MessageConstants.Messages[CurrentMessageIndex].PromptsResponse, false, CurrentMessageIndex > LastTutorialMessageIdx);
			CurrentMessageIndex++;
		}
	}
}

void Ajuicejam2GameModeBase::BeginPlay()
{
	if(TerminalUIWidgetClass)
	{
		UTerminalUIWidget* TerminalUIWidgetLocal = CreateWidget<UTerminalUIWidget>(GetWorld(), TerminalUIWidgetClass);
		
		if(TerminalUIWidgetLocal)
		{
			TerminalUIWidget = TerminalUIWidgetLocal;
			
			TerminalUIWidget->AddToViewport();

			if(MessageConstants.Messages.Num() > 0)
			{
				TerminalUIWidget->AddMessage(FText::FromString(MessageConstants.Messages[CurrentMessageIndex].Message), true, 0, MessageConstants.Messages[CurrentMessageIndex].PromptsResponse);
				CurrentMessageIndex++;
			}

			TerminalUIWidget->OnPromptEnd.AddDynamic(this, &Ajuicejam2GameModeBase::OnPromptEnd);
		}
	}

	if(StateHUDClass)
	{
		StateHUD = CreateWidget<UStateHUD>(GetWorld(), StateHUDClass);
		
		if(StateHUD)
		{
			StateHUD->AddToViewport();
			StateHUD->SetElectricityLevel(1.f);
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
