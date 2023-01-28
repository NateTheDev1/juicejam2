// Nathaniel Richards All Rights Reserved 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "TerminalUIWidget.generated.h"

UCLASS()
class JUICEJAM2_API UTerminalUIWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// UPROPERTY(EditAnywhere, Category="Config")
	// FSlateFontInfo MessageTextFont;

	FTimerHandle SetTextTimerHandle;

	void SetTextAfterDelay(UTextBlock *TextBlock, wchar_t Character, FTimerHandle TimerHandle);
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* MessageBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* InputText;
public:
	void AddMessage(const FText& Message);

	virtual void NativeConstruct() override;
};
