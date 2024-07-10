// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindInputActionForTag(FGameplayTag& Tag, bool bLogNotFound) const
{
	for (const FAuraInputAction Action : AbilityInputAction)
	{
		if (Action.InputAction && Action.InputTag.MatchesTag(Tag))
		{
			return Action.InputAction;
		}
	}

	if(bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("不能在[ %s ]上找到名为 [ %s ] 的 Tag"), *GetNameSafe(this) ,*Tag.ToString());
	}
	return nullptr;
}
