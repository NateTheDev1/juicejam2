// Nathaniel Richards All Rights Reserved 2023


#include "TerminalUIWidget.h"

void UTerminalUIWidget::AddMessage(const FText& Message)
{
	// Create a new text block
	UTextBlock* TextBlock = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
	// TextBlock->SetFont(MessageTextFont);
	MessageBox->AddChild(TextBlock);
	TextBlock->SetRenderScale(FVector2d(1,-1));

	float AppendingTime = 0;
	
	for(auto Character : Message.ToString())
	{
		AppendingTime += 0.05f;
		FTimerHandle TimerHandle = FTimerHandle();
		
		FTimerDelegate SetTextAfterDelayDelegate = FTimerDelegate::CreateUObject(this, &UTerminalUIWidget::SetTextAfterDelay, TextBlock, Character, TimerHandle);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, SetTextAfterDelayDelegate, 0.05f + AppendingTime, false);
	}
}

void UTerminalUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// Reset to default.
	InputText->SetText(FText::FromString(""));
}

void UTerminalUIWidget::SetTextAfterDelay(UTextBlock* TextBlock, wchar_t Character, FTimerHandle TimerHandle)
{
	if(SetTextTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(SetTextTimerHandle);
	}
	
	FText CurrentText = TextBlock->GetText();

	FString NewLetter = FString::Chr(Character);
	
	FString NewText = FString::Format(TEXT("{0}{1}"), {CurrentText.ToString(), NewLetter});
	TextBlock->SetText(FText::FromString(NewText));
}
