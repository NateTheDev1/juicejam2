// Nathaniel Richards All Rights Reserved 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

UCLASS()
class JUICEJAM2_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category="Config")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	
	virtual void BeginPlay() override;
};
