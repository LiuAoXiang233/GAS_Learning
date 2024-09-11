// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVM_ViewModelBase.h"
#include "MVVM_LoadScreenModel.generated.h"

/**
 * 
 */
class UMVVM_LoadMenuSoltModel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectSlot, int32, SlotIndex);

UCLASS()
class GAS_LEARNING_DEMO_API UMVVM_LoadScreenModel : public UMVVM_ViewModelBase
{
	GENERATED_BODY()

	

public:

	/*
		 *	Setter
		 */
	void SetSelectSlotIndex(int32 InSelectSlotIndex);
	

	/*
	 *	Setter End
	 */

	/*
	 *	Getter
	 */
	int32 GetSelectSlotIndex() const {return SelectSlotIndex;}

	/*
	 *	Getter End
	 */
	
	UPROPERTY(BlueprintAssignable)
	FOnSelectSlot SelectSlotDelegate;

	UFUNCTION(BlueprintCallable)
	void SelectSlot(int32 Index);
	
	UFUNCTION(BlueprintCallable)
	void InitializeSlotWidgetViewModel();

	UFUNCTION(BlueprintPure)
	UMVVM_LoadMenuSoltModel* GetLoadSoltMenuModel(int32 index = 0) const;

	UFUNCTION(BlueprintCallable)
	void SaveGameButtonPressed();

	UFUNCTION(BlueprintCallable)
	void LoadData();

	UFUNCTION(BlueprintCallable)
    void DeleteButtonPressed(); 

	UFUNCTION(BlueprintCallable)
	void PlayGameButtonPressed();




	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMVVM_ViewModelBase> SlotWidgetMenuViewModelClass;

	UPROPERTY()
	TMap<int32, UMVVM_LoadMenuSoltModel*> LoadSlots;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadMenuSoltModel> LoadMenuSoltModel_Default;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadMenuSoltModel> LoadMenuSoltModel_1;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadMenuSoltModel> LoadMenuSoltModel_2;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadMenuSoltModel> LoadMenuSoltModel_3;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadMenuSoltModel> LoadMenuSoltModel_4;

private:

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, FieldNotify, Setter,Getter,meta=(AllowPrivateAccess = "true"))
	int32 SelectSlotIndex = 0;
	
};
