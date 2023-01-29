// Nathaniel Richards All Rights Reserved 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "TerminalUIWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPromptStart, int32, InstanceID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPromptResponseEnd, int32, InstanceID);

UCLASS()
class JUICEJAM2_API UTerminalUIWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Config")
	FSlateFontInfo MessageTextFont;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* MessageBox;
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* InputText;

	void OnPromptComplete(FString InputString);
	
	void AddMessage(const FText& Message, bool bCallbackUsePrompt, int32 CallbackInstanceID, bool bRequiresReponseFromPrompt = false, bool bIsResponsePrint = false);

	void PromptResponse(int32 InstanceID);

	virtual void NativeConstruct() override;

	void DisplayNextLetter();

	bool bIsTransmittingMessage = false;

	bool bIsWaitingForPromptResponse = false;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Delegates")
	FOnPromptStart OnPromptStart;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Delegates")
	FOnPromptResponseEnd OnPromptEnd;

	FText CurrentMessage;
	
private:
	FString CurrentString;
	int32 CurrentIndex;
	float CharDelay = 0.001f;
	int32 StringLength;

	bool bUsePromptCallback = false;
	bool bRequiresReponse = false;
	bool bIsResponsePrinted = false;

	int32 PromptCallbackInstanceID = 0;
	
	UPROPERTY()
	UTextBlock* CurrentTextBlock;
	
	FTimerHandle TimerHandle;
};
