// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MVVM/MVVM_ViewModelBase.h"

void UMVVM_ViewModelBase::SetWidgetName(FString InWidgetName)
{
	UE_MVVM_SET_PROPERTY_VALUE(WidgetName, InWidgetName);
}
