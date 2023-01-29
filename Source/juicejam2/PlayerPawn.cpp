// Nathaniel Richards All Rights Reserved 2023

#include "PlayerPawn.h"

#include "TerminalUIWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Char.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerPawn::PromptResponse(int32 InstanceID)
{
	CurrentString = "";
}

void APlayerPawn::BeginPlay()
{
	TArray<UUserWidget*> TerminalUIWidgetSearch;
	
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), TerminalUIWidgetSearch, UTerminalUIWidget::StaticClass(), false);
	
	if(TerminalUIWidgetSearch.Num() > 0)
	{
		Widget = Cast<UTerminalUIWidget>(TerminalUIWidgetSearch[0]);
	}

	if(Widget)
	{
		Widget->OnPromptStart.AddDynamic(this, &APlayerPawn::PromptResponse);
	}
	
	Super::BeginPlay();
	
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindKey(EKeys::AnyKey, IE_Pressed, this, &APlayerPawn::OnAnyKeyPressed);
}

void APlayerPawn::OnAnyKeyPressed(FKey Key)
{
	if(Widget->bIsTransmittingMessage)
	{
		return;
	}

	TCHAR Char = Key.GetDisplayName().ToString().GetCharArray()[0];
	
	if(Widget->bIsWaitingForPromptResponse && Key != EKeys::Enter && Key.GetDisplayName().ToString().Len() == 1 && FChar::IsAlpha(Char))
	{
		
		if(Widget->CurrentMessage.ToString().Contains("(Y/N"))
		{
			if(Key.GetDisplayName().ToString() != "Y" && Key.GetDisplayName().ToString() != "N")
			{
				return;
			}
		}
		
		CurrentString += Key.GetDisplayName().ToString();

		Widget->InputText->SetText(FText::FromString(CurrentString));
	} else if (Widget->bIsWaitingForPromptResponse && Key == EKeys::Enter)
	{
		Widget->OnPromptComplete(CurrentString);
	}
}

