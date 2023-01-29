// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateHUD.h"
#include "TerminalUIWidget.h"
#include "GameFramework/GameModeBase.h"
#include "juicejam2GameModeBase.generated.h"

USTRUCT()
struct FMessageConstantMessage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FString Message;

	UPROPERTY()
	bool PromptsResponse;

	UPROPERTY()
	FString RightResponse;

	UPROPERTY()
	float EmpathyHit;
};

USTRUCT()
struct FMessageConstants
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY()
	TArray<FMessageConstantMessage> Messages;
};

UCLASS()
class JUICEJAM2_API Ajuicejam2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category="Config")
	USoundBase* AmbianceSound;
	
	UPROPERTY(EditAnywhere, Category="Config")
	TSubclassOf<UTerminalUIWidget> TerminalUIWidgetClass;

	UPROPERTY(EditAnywhere, Category="Config")
	TSubclassOf<UStateHUD> StateHUDClass;

	virtual void BeginPlay() override;

	Ajuicejam2GameModeBase();

	void OnResponse(int32 InstanceID, FString Response);
private:
	const int32 LastTutorialMessageIdx = 6;
protected:
	UPROPERTY()
	UTerminalUIWidget* TerminalUIWidget;

	UPROPERTY()
	UStateHUD* StateHUD;
	
	FMessageConstants MessageConstants;

	UFUNCTION()
	void OnPromptEnd(int32 InstanceID);

	int32 CurrentMessageIndex = 0;
	
	void InitializeMessageConstants();
	
	static FString ReadStringFromFile(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage);
	static TSharedPtr<FJsonObject> ReadJson(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage);
};
