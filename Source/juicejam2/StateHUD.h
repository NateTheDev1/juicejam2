// Nathaniel Richards All Rights Reserved 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "StateHUD.generated.h"

UCLASS()
class JUICEJAM2_API UStateHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation *ElectricShakeAnim;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar *ElectricityBar;

	UPROPERTY()
	float ElectricityLevel = 1.0f;

	UPROPERTY()
	float EmpathyLevel = 1.0f;

	void SetElectricityLevel(float NewLevel);
	void SetEmpathyLevel(float NewLevel);
};
