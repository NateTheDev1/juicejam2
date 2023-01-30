// Nathaniel Richards All Rights Reserved 2023


#include "MainMenuWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(QuitBtn)
	{
		QuitBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClick);
	}

	if(StartBtn)
	{
		StartBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartClick);
	}
}

void UMainMenuWidget::OnStartClick()
{
	UWorld* World = GetWorld();
	
	if(World)
	{
		UGameplayStatics::OpenLevel(World, TEXT("MainLevel"));
	}
}

void UMainMenuWidget::OnQuitClick()
{
	UWorld* World = GetWorld();
	
	if(World)
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World, TEXT("quit"));
	}
}
