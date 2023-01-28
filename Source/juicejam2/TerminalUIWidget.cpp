// Nathaniel Richards All Rights Reserved 2023


#include "TerminalUIWidget.h"

#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"

void UTerminalUIWidget::AddMessage(const FText& Message, bool bCallbackUsePrompt, int32 CallbackInstanceID)
{
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if(PlayerPawn)
	{
		PlayerPawn->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	}
	
	bUsePromptCallback = bCallbackUsePrompt;
	PromptCallbackInstanceID = CallbackInstanceID;
	
	bIsTransmittingMessage = true;
	// Create a new text block
	UTextBlock* TextBlock = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
	// TextBlock->SetFont(MessageTextFont);
	MessageBox->AddChild(TextBlock);
	TextBlock->SetRenderScale(FVector2d(1,-1));
	TextBlock->SetAutoWrapText(true);

	CurrentTextBlock = TextBlock;

	StringLength = Message.ToString().Len();
	CurrentIndex = 0;
	CurrentString = "";
	CurrentMessage = Message;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UTerminalUIWidget::DisplayNextLetter, CharDelay, false);

}

void UTerminalUIWidget::PromptResponse(int32 InstanceID)
{
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if(PlayerPawn)
	{
		PlayerPawn->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	}
}

void UTerminalUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// Reset to default.
	InputText->SetText(FText::FromString(""));
}

void UTerminalUIWidget::DisplayNextLetter()
{
	CurrentString.AppendChar(CurrentMessage.ToString()[CurrentIndex]);
	CurrentTextBlock->SetText(FText::FromString(CurrentString));

	CurrentIndex++;

	if(CurrentIndex >= StringLength)
	{
		bIsTransmittingMessage = false;

		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

		if(bUsePromptCallback)
		{
			PromptResponse(PromptCallbackInstanceID);
		}
		
		return;
	}

	float Delay = CharDelay;
	if (CurrentMessage.ToString()[CurrentIndex - 1] == '.' || CurrentMessage.ToString()[CurrentIndex - 1] == '!' || CurrentMessage.ToString()[CurrentIndex - 1] == '?') {
		Delay += 1.f;
	}
	
	if (CurrentIndex < StringLength)
	{
		// Set the timer to call this function again with the next letter
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UTerminalUIWidget::DisplayNextLetter, Delay, false);
	} else
	{
		bIsTransmittingMessage = false;
		
		if(bUsePromptCallback)
		{
			PromptResponse(PromptCallbackInstanceID);
		}
	}
}