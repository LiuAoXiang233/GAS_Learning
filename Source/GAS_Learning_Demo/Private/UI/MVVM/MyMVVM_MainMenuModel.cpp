// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MVVM/MyMVVM_MainMenuModel.h"


void UMyMVVM_MainMenuModel::SetWidgetName(FString InWidgetName)
{
	UE_MVVM_SET_PROPERTY_VALUE(WidgetName, InWidgetName);
}

void UMyMVVM_MainMenuModel::StartButtonPressed()
{

	
}

void UMyMVVM_MainMenuModel::ContinueButtonPressed()
{
	OpenLoadMenuDelegate.Broadcast();

}

void UMyMVVM_MainMenuModel::ExitButtonPressed()
{


}
