// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AuraInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityFunc(UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UAuraInputComponent::BindAbilityFunc(UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc,
	ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig)

	for (const FAuraInputAction& InputAction : InputConfig->AbilityInputAction)
	{
		if(InputAction.InputAction && InputAction.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(InputAction.InputAction, ETriggerEvent::Started, Object, PressedFunc, InputAction.InputTag);
			}

			if (ReleasedFunc)
			{
				BindAction(InputAction.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, InputAction.InputTag);
			}
			if (HeldFunc)
			{
				BindAction(InputAction.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, InputAction.InputTag);
			}

			
		}
	}
}
