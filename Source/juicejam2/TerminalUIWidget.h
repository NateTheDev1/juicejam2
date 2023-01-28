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
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* MessageBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* InputText;
public:
	void AddMessage(const FText& Message, bool bCallbackUsePrompt, int32 CallbackInstanceID);

	void PromptResponse(int32 InstanceID);

	virtual void NativeConstruct() override;

	void DisplayNextLetter();

	bool bIsTransmittingMessage = false;
	
private:
	FString CurrentString;
	int32 CurrentIndex;
	FText CurrentMessage;
	float CharDelay = 0.02f;
	int32 StringLength;

	bool bUsePromptCallback = false;

	int32 PromptCallbackInstanceID = 0;
	
	UPROPERTY()
	UTextBlock* CurrentTextBlock;
	
	FTimerHandle TimerHandle;
};
