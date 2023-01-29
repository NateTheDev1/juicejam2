// Nathaniel Richards All Rights Reserved 2023


#include "StateHUD.h"

#include "Kismet/GameplayStatics.h"

void UStateHUD::SetElectricityLevel(float NewLevel)
{
	ElectricityLevel = NewLevel;
	ElectricityBar->SetPercent(ElectricityLevel);

	UGameplayStatics::PlaySound2D(GetWorld(), PowerDownSound, 0.5f, 1.0f, 0.0f);
	
	PlayAnimation(ElectricShakeAnim, 0, 5);
}

void UStateHUD::SetEmpathyLevel(float NewLevel)
{
	EmpathyLevel = NewLevel;
}

void UStateHUD::NativeConstruct()
{
	Super::NativeConstruct();

	ToggleTimerVisibility();
}

void UStateHUD::ToggleTimerVisibility() const
{
	if (CountdownImage->GetVisibility() == ESlateVisibility::Hidden)
	{
		CountdownImage->SetVisibility(ESlateVisibility::Visible);
		CountdownText->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		CountdownImage->SetVisibility(ESlateVisibility::Hidden);
		CountdownText->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UStateHUD::SetTimerTime(float Time) const
{
	CountdownText->SetText(FText::FromString(FString::SanitizeFloat(Time)));
}
