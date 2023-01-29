// Nathaniel Richards All Rights Reserved 2023


#include "TerminalUIWidget.h"

#include "PlayerPawn.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/ScrollBoxSlot.h"
#include "Kismet/GameplayStatics.h"

void UTerminalUIWidget::OnPromptComplete(FString InputString)
{
	bIsWaitingForPromptResponse = false;
	
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	InputText->SetText(FText::FromString(""));
	
	AddMessage( FText::FromString("Your Response: " + InputString), false, -1, false);
}

void UTerminalUIWidget::AddMessage(const FText& Message, bool bCallbackUsePrompt, int32 CallbackInstanceID, bool bRequiresReponseFromPrompt, bool bIsResponsePrint)
{
	bIsResponsePrinted = bIsResponsePrint;
	
	UE_LOG(LogTemp, Warning, TEXT("AddMessage %s"), *Message.ToString());
	
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if(PlayerPawn)
	{
		PlayerPawn->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	}

	bRequiresReponse = bRequiresReponseFromPrompt;
	
	bUsePromptCallback = bCallbackUsePrompt;
	PromptCallbackInstanceID = CallbackInstanceID;
	
	bIsTransmittingMessage = true;
	// Create a new text block
	UTextBlock* TextBlock = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
	
	TextBlock->SetFont(MessageTextFont);
	
	MessageBox->AddChild(TextBlock);
	
	TArray<UWidget*> Children = MessageBox->GetAllChildren();

	TArray<UWidget*> NewChildren = TArray<UWidget*>();
	
	for(int i = Children.Num() - 1; i >= 0; i--)
	{
		NewChildren.Add(Children[i]);
	}

	// Every child is formatted by the name TextBlock_# sort it and then add
	NewChildren.Sort([](const UWidget& A, const UWidget& B) {
		return A.GetName() > B.GetName();
	});
	
	MessageBox->ClearChildren();
	
	for(int i = 0; i < NewChildren.Num(); i++)
	{
		MessageBox->AddChild(NewChildren[i]);
	}

	TArray<UPanelSlot*> slots = MessageBox->GetSlots();
	
	for (UPanelSlot* slot : slots)
	{
		if (UScrollBoxSlot* sSlot = Cast<UScrollBoxSlot>(slot))
			sSlot->SetPadding(FMargin(0, 0, 0, 20.0f));
	}
	
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
	if(bRequiresReponse)
	{
		bIsWaitingForPromptResponse = true;
		OnPromptStart.Broadcast(InstanceID);
	
		APlayerPawn* PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

		if(PlayerPawn)
		{
			PlayerPawn->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		}
	} else
	{
		OnPromptEnd.Broadcast(InstanceID);
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
	if(CurrentMessage.ToString().Len() == 1)
	{
		CurrentTextBlock->SetText(CurrentMessage);
		bIsTransmittingMessage = false;
		OnPromptEnd.Broadcast(PromptCallbackInstanceID);
	}
	
	CurrentString.AppendChar(CurrentMessage.ToString()[CurrentIndex]);
	CurrentTextBlock->SetText(FText::FromString(CurrentString));

	CurrentIndex++;

	if(CurrentIndex >= StringLength)
	{
		bIsTransmittingMessage = false;

		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

		if(bRequiresReponse)
		{
			PromptResponse(PromptCallbackInstanceID);
			return;
		}

		if(!bIsTransmittingMessage)
		{
			OnPromptEnd.Broadcast(PromptCallbackInstanceID);
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
		
		if(bUsePromptCallback && bRequiresReponse)
		{
			PromptResponse(PromptCallbackInstanceID);
		}
	}
}