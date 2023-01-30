// Nathaniel Richards All Rights Reserved 2023


#include "MainMenuGameMode.h"
#include "Blueprint/UserWidget.h"

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(MainMenuWidgetClass))
	{
		UUserWidget* Widget = CreateWidget(GetWorld(), MainMenuWidgetClass);

		if(Widget)
		{
			Widget->AddToViewport();
		}
	}
}
