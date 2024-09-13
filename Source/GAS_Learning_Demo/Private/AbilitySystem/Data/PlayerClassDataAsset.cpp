// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/PlayerClassDataAsset.h"

FPlayerClassData UPlayerClassDataAsset::FindPlayerClassDataForTag(const FGameplayTag& PlayerClassTag,
	bool bLogNotFound) const
{
	for (const FPlayerClassData& PlayerData : PlayerClassDatas)
	{
		if (PlayerData.PlayerClassTag == PlayerClassTag)
		{
			return PlayerData;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("不能从 Player Class Datas 中找到 [%s]"),*PlayerClassTag.ToString());
	}
	
	return FPlayerClassData();
}
