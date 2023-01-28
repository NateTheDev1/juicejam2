// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TerminalUIWidget.h"
#include "GameFramework/GameModeBase.h"
#include "juicejam2GameModeBase.generated.h"

USTRUCT()
struct FMessageConstants
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY()
	TArray<FString> Messages;
};

UCLASS()
class JUICEJAM2_API Ajuicejam2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category="Config")
	TSubclassOf<UTerminalUIWidget> TerminalUIWidgetClass;

	virtual void BeginPlay() override;

	Ajuicejam2GameModeBase();

protected:
	FMessageConstants MessageConstants;
	
	void InitializeMessageConstants();
	
	static FString ReadStringFromFile(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage);
	static TSharedPtr<FJsonObject> ReadJson(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage);
};
