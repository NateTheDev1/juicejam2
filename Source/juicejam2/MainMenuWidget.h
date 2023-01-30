// Nathaniel Richards All Rights Reserved 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenuWidget.generated.h"

UCLASS()
class JUICEJAM2_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* StartBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* QuitBtn;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnStartClick();

	UFUNCTION()
	void OnQuitClick();
};
