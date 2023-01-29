// Nathaniel Richards All Rights Reserved 2023

#pragma once

#include "CoreMinimal.h"
#include "TerminalUIWidget.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class JUICEJAM2_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawn();

protected:
	UFUNCTION()
	void PromptResponse(int32 InstanceID);

	FString CurrentString;
	
	virtual void BeginPlay() override;

	UPROPERTY()
	UTerminalUIWidget* Widget;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnAnyKeyPressed(FKey Key);
};
