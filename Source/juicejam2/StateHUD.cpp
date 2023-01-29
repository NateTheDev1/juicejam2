// Nathaniel Richards All Rights Reserved 2023


#include "StateHUD.h"

void UStateHUD::SetElectricityLevel(float NewLevel)
{
	ElectricityLevel = NewLevel;
	ElectricityBar->SetPercent(ElectricityLevel);
	
	PlayAnimation(ElectricShakeAnim, 0, 5);
}

void UStateHUD::SetEmpathyLevel(float NewLevel)
{
	EmpathyLevel = NewLevel;
}
