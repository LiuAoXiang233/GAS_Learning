// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AuraGameModeBase.h"

#include "EngineUtils.h"
#include "Game/AuraGameInstance.h"
#include "Game/LoadScreenSaveGame.h"
#include "GameFramework/PlayerStart.h"
#include "Interaction/BeSavedInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "UI/MVVM/MVVM_LoadMenuSoltModel.h"

void AAuraGameModeBase::SaveSlotData(UMVVM_LoadMenuSoltModel* LoadSlotModel, const int32 SlotIndex)
{
	if (UGameplayStatics::DoesSaveGameExist(LoadSlotModel->LoadSlotName, SlotIndex))
	{
		UGameplayStatics::DeleteGameInSlot(LoadSlotModel->LoadSlotName, SlotIndex);
	}

	USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(LoadScreenSaveGameClass);
	ULoadScreenSaveGame* LoadScreenSaveGame = Cast<ULoadScreenSaveGame>(SaveGameObject);
	
	// LoadScreenSaveGame->PlayerName = LoadSlotModel->GetPlayerName(); 存档中的玩家名字不从此处设置
	LoadScreenSaveGame->SaveSlotStatus = ESaveSlotStatus::Taken;
	LoadScreenSaveGame->MapName = LoadSlotModel->GetMapName();

	UGameplayStatics::SaveGameToSlot(LoadScreenSaveGame, LoadSlotModel->LoadSlotName, SlotIndex);
	
}

void AAuraGameModeBase::TravelToMap(UMVVM_LoadMenuSoltModel* LoadSlotModel)
{
	const FString MapName = LoadSlotModel->GetMapName();
	TSoftObjectPtr<UWorld> Level = Maps.FindChecked(MapName);
	
	UGameplayStatics::OpenLevelBySoftObjectPtr(LoadSlotModel, Level);
}

ULoadScreenSaveGame* AAuraGameModeBase::RetrieveInGameSaveData()
{
	if (UAuraGameInstance* GameInstance = Cast<UAuraGameInstance>(GetGameInstance()))
	{
		FString InLoadSlotName = GameInstance->LoadSlotName;
		int32 InLoadSlotIndex = GameInstance->LoadSlotIndex;

		return GetSaveSlotData(InLoadSlotName, InLoadSlotIndex);
	}

	return nullptr;
	
}

void AAuraGameModeBase::SaveInGameSaveData(ULoadScreenSaveGame* SaveGameData)
{
	if (UAuraGameInstance* GameInstance = Cast<UAuraGameInstance>(GetGameInstance()))
	{
		FString InLoadSlotName = GameInstance->LoadSlotName;
		int32 InLoadSlotIndex = GameInstance->LoadSlotIndex;
		SaveGameData->SaveSlotStatus = ESaveSlotStatus::Taken;
		UGameplayStatics::SaveGameToSlot(SaveGameData, InLoadSlotName, InLoadSlotIndex);
	}
}



// MainMenuViewMode 和 CharacterSettingViewModel 不要使用
ULoadScreenSaveGame* AAuraGameModeBase::GetSaveSlotData(const FString& SlotName, int32 SlotIndex) const
{
	// 这是从当前选择的存档中获取 Save Game Data
	USaveGame* SaveGameObject = nullptr;
	if (UGameplayStatics::DoesSaveGameExist(SlotName, SlotIndex))
	{
		SaveGameObject = UGameplayStatics::LoadGameFromSlot(SlotName, SlotIndex);
	}
	
	else
	{
		SaveGameObject = UGameplayStatics::CreateSaveGameObject(LoadScreenSaveGameClass);
	}

	ULoadScreenSaveGame* LoadSaveGame = Cast<ULoadScreenSaveGame>(SaveGameObject);
	
	return LoadSaveGame;
	
}

void AAuraGameModeBase::SaveWorldState(UWorld* World) const
{
	FString MapName = World->GetMapName();
	MapName.RemoveFromStart(World->StreamingLevelsPrefix);

	UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(GetGameInstance());
	check(AuraGameInstance);

	if (ULoadScreenSaveGame* SaveGame = GetSaveSlotData(AuraGameInstance->LoadSlotName, AuraGameInstance->LoadSlotIndex))
	{
		if (!SaveGame->HasMap(MapName))
		{
			FSavedMap Map = FSavedMap();
			Map.MapAssetName = MapName;
			SaveGame->SavedMaps.Add(Map);
		}

		FSavedMap SavedMap = SaveGame->GetSaveMapWithMapName(MapName);
		
		SavedMap.SavedActors.Empty();

		// 将场景中的所有要保存的事物保存在存档中
		for (FActorIterator It(World); It; ++It)
		{
			AActor* Actor = *It;
			if (!IsValid(Actor) || !Actor->Implements<UBeSavedInterface>()) continue;

			FSavedActor SavedActor;
			SavedActor.Transform = Actor->GetTransform();
			SavedActor.ActorName = Actor->GetFName();

			// 创建写入器
			FMemoryWriter MemoryWriter(SavedActor.Bytes);
			// 创建翻译器
			FObjectAndNameAsStringProxyArchive Archive(MemoryWriter, true);
			// 设置翻译器标识
			Archive.ArIsSaveGame = true;				// 仅将带有 UPROPERTY(SaveGame) 的属性进行序列化
			// 将 Actor 写入 Archive
			Actor->Serialize(Archive);
			
			SavedMap.SavedActors.AddUnique(SavedActor);
		}

		for (FSavedMap& MapToReplace : SaveGame->SavedMaps)
		{
			if (MapToReplace.MapAssetName == MapName)
			{
				MapToReplace = SavedMap;
			}
		}

		UGameplayStatics::SaveGameToSlot(SaveGame, AuraGameInstance->LoadSlotName, AuraGameInstance->LoadSlotIndex);
	}
}

void AAuraGameModeBase::LoadWorldState(UWorld* World) const
{
	FString MapName = World->GetMapName();
	MapName.RemoveFromStart(World->StreamingLevelsPrefix);

	UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(GetGameInstance());
	check(AuraGameInstance);

	if (UGameplayStatics::DoesSaveGameExist(AuraGameInstance->LoadSlotName, AuraGameInstance->LoadSlotIndex))
	{
		for (FActorIterator It(World); It; ++It)
		{
			AActor* Actor = *It;
			ULoadScreenSaveGame* SaveGame = Cast<ULoadScreenSaveGame>(UGameplayStatics::LoadGameFromSlot(AuraGameInstance->LoadSlotName, AuraGameInstance->LoadSlotIndex));
			if (!Actor->Implements<UBeSavedInterface>()) continue;
			for (FSavedActor SavedActor : SaveGame->GetSaveMapWithMapName(MapName).SavedActors)
			{
				if (SavedActor.ActorName == Actor->GetFName())
				{
					
					Actor->SetActorTransform(SavedActor.Transform);
					// 创建阅读器
					FMemoryReader MemoryReader(SavedActor.Bytes,true);
                        
					// 创建翻译器
					FObjectAndNameAsStringProxyArchive Ar(MemoryReader, true);
                        
					// 设置翻译器标识
					Ar.ArIsSaveGame = true;
					// 将 ObjectData 写入 Object
					Actor->Serialize(Ar);
                        
					// TODO: 对Actor进行操作
					IBeSavedInterface::Execute_BeLoaded(Actor);
					
					
					
				}
			}
		}
	}
}

AActor* AAuraGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{

	UAuraGameInstance* GameInstance = Cast<UAuraGameInstance>(GetGameInstance());
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), Actors);
	if (Actors.Num() > 0)
	{
		AActor* ChooseActor = Actors[0];

		for (AActor* Actor : Actors)
		{
			if (APlayerStart* PlayerStart = Cast<APlayerStart>(Actor))
			{
				if (PlayerStart->PlayerStartTag == GameInstance->PlayerStartTag)
				{
					ChooseActor = Actor;
					break;
				}
			}
		}
		return ChooseActor;
	}
	return nullptr;
}

void AAuraGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Maps.Add(DefaultMapName, DefaultMap);
}
