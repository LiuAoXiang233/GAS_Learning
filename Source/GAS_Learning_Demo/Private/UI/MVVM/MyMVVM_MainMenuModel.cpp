// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MVVM/MyMVVM_MainMenuModel.h"


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
