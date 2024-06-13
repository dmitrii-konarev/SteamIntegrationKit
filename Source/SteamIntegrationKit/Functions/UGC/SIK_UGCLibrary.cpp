﻿// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_UGCLibrary.h"

bool USIK_UGCLibrary::AddExcludedTag(FSIK_UGCQueryHandle QueryHandle, const FString& TagName)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->AddExcludedTag(QueryHandle.GetUGCQueryHandle(), TCHAR_TO_UTF8(*TagName));
}

bool USIK_UGCLibrary::AddItemKeyValueTag(FSIK_UGCUpdateHandle UpdateHandle, const FString& Key, const FString& Value)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->AddItemKeyValueTag(UpdateHandle.GetUGCUpdateHandle(), TCHAR_TO_UTF8(*Key), TCHAR_TO_UTF8(*Value));
}

bool USIK_UGCLibrary::AddItemPreviewFile(FSIK_UGCUpdateHandle UpdateHandle, const FString& PreviewFile,
	TEnumAsByte<ESIK_ItemPreviewType> FileType)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->AddItemPreviewFile(UpdateHandle.GetUGCUpdateHandle(), TCHAR_TO_UTF8(*PreviewFile), static_cast<EItemPreviewType>(FileType.GetValue()));
}

bool USIK_UGCLibrary::AddItemPreviewVideo(FSIK_UGCUpdateHandle UpdateHandle, const FString& VideoID)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->AddItemPreviewVideo(UpdateHandle.GetUGCUpdateHandle(), TCHAR_TO_UTF8(*VideoID));
}

bool USIK_UGCLibrary::AddRequiredKeyValueTag(FSIK_UGCUpdateHandle UpdateHandle, const FString& Key, const FString& Value)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->AddRequiredKeyValueTag(UpdateHandle.GetUGCUpdateHandle(), TCHAR_TO_UTF8(*Key), TCHAR_TO_UTF8(*Value));
}

bool USIK_UGCLibrary::AddRequiredTag(FSIK_UGCQueryHandle QueryHandle, const FString& TagName)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->AddRequiredTag(QueryHandle.GetUGCQueryHandle(), TCHAR_TO_UTF8(*TagName));
}

bool USIK_UGCLibrary::AddRequiredTagGroup(FSIK_UGCQueryHandle QueryHandle, const TArray<FString>& TagNames)
{
	if(!SteamUGC())
	{
		return false;
	}
	TArray<const char*> TagNamesArray;
	for(const FString& TagName : TagNames)
	{
		TagNamesArray.Add(TCHAR_TO_UTF8(*TagName));
	}
	SteamParamStringArray_t* ParamArray = new SteamParamStringArray_t();
	ParamArray->m_ppStrings = TagNamesArray.GetData();
	ParamArray->m_nNumStrings = TagNamesArray.Num();
	return SteamUGC()->AddRequiredTagGroup(QueryHandle.GetUGCQueryHandle(), ParamArray);
}

bool USIK_UGCLibrary::BInitWorkshopForGameServer(FSIK_DepotId DepotId, const FString& Folder)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->BInitWorkshopForGameServer(DepotId.GetDepotID(), TCHAR_TO_UTF8(*Folder));
}

FSIK_UGCQueryHandle USIK_UGCLibrary::CreateQueryAllUGCRequest(TEnumAsByte<ESIK_UGCQuery> QueryType,
	TEnumAsByte<ESIK_UGCMatchingUGCType> MatchingType, FSIK_AppId CreatorAppID, FSIK_AppId ConsumerAppID, int32 Page)
{
	if(!SteamUGC())
	{
		return FSIK_UGCQueryHandle();
	}
	return FSIK_UGCQueryHandle(SteamUGC()->CreateQueryAllUGCRequest(static_cast<EUGCQuery>(QueryType.GetValue()), static_cast<EUGCMatchingUGCType>(MatchingType.GetValue()), CreatorAppID.GetAppID(), ConsumerAppID.GetAppID(), Page));
}

FSIK_UGCQueryHandle USIK_UGCLibrary::CreateQueryUGCDetailsRequest(TArray<FSIK_PublishedFileId> PublishedFileIDs)
{
	if(!SteamUGC())
	{
		return FSIK_UGCQueryHandle();
	}
	TArray<PublishedFileId_t> PublishedFileIDsArray;
	for(const FSIK_PublishedFileId& PublishedFileID : PublishedFileIDs)
	{
		PublishedFileIDsArray.Add(PublishedFileID.GetPublishedFileId());
	}
	return SteamUGC()->CreateQueryUGCDetailsRequest(PublishedFileIDsArray.GetData(), PublishedFileIDsArray.Num());
}

FSIK_UGCQueryHandle USIK_UGCLibrary::CreateQueryUserUGCRequest(FSIK_AccountID AccountID,
	TEnumAsByte<ESIK_UserUGCList> ListType, TEnumAsByte<ESIK_UGCMatchingUGCType> MatchingType,
	TEnumAsByte<ESIK_UserUGCListSortOrder> SortOrder, FSIK_AppId CreatorAppID, FSIK_AppId ConsumerAppID, int32 Page)
{
	if(!SteamUGC())
	{
		return FSIK_UGCQueryHandle();
	}
	return SteamUGC()->CreateQueryUserUGCRequest(AccountID.GetAccountID(), static_cast<EUserUGCList>(ListType.GetValue()), static_cast<EUGCMatchingUGCType>(MatchingType.GetValue()), static_cast<EUserUGCListSortOrder>(SortOrder.GetValue()), CreatorAppID.GetAppID(), ConsumerAppID.GetAppID(), Page);
}

bool USIK_UGCLibrary::DownloadItem(FSIK_PublishedFileId PublishedFileId, bool bHighPriority)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->DownloadItem(PublishedFileId.GetPublishedFileId(), bHighPriority);
}

bool USIK_UGCLibrary::GetAppDependencies(FSIK_PublishedFileId PublishedFileId)
{
	if(!SteamUGC())
	{
		return false;
	}
	SteamUGC()->GetAppDependencies(PublishedFileId.GetPublishedFileId());
	return true;
}

bool USIK_UGCLibrary::GetItemDownloadInfo(FSIK_PublishedFileId PublishedFileId, int64& BytesDownloaded,
	int64& BytesTotal)
{
	if(!SteamUGC())
	{
		return false;
	}
	uint64 BytesDownloaded64;
	uint64 BytesTotal64;
	bool bResult = SteamUGC()->GetItemDownloadInfo(PublishedFileId.GetPublishedFileId(), &BytesDownloaded64, &BytesTotal64);
	BytesDownloaded = BytesDownloaded64;
	BytesTotal = BytesTotal64;
	return bResult;
}

bool USIK_UGCLibrary::GetItemInstallInfo(FSIK_PublishedFileId PublishedFileId, int64& SizeOnDisk, FString& Folder,
	int32& TimeStamp)
{
	if(!SteamUGC())
	{
		return false;
	}
	uint64 SizeOnDisk64;
	char FolderBuffer[1024];
	uint32 TimeStamp32;
	bool bResult = SteamUGC()->GetItemInstallInfo(PublishedFileId.GetPublishedFileId(), &SizeOnDisk64, FolderBuffer, 1024, &TimeStamp32);
	SizeOnDisk = SizeOnDisk64;
	Folder = FString(UTF8_TO_TCHAR(FolderBuffer));
	TimeStamp = TimeStamp32;
	return bResult;
}

int32 USIK_UGCLibrary::GetItemState(FSIK_PublishedFileId PublishedFileId)
{
	if(!SteamUGC())
	{
		return 0;
	}
	return SteamUGC()->GetItemState(PublishedFileId.GetPublishedFileId());
}

TEnumAsByte<ESIK_ItemUpdateStatus> USIK_UGCLibrary::GetItemUpdateProgress(FSIK_UGCUpdateHandle UpdateHandle,
	int64& BytesProcessed, int64& BytesTotal)
{
	if(!SteamUGC())
	{
		return ESIK_ItemUpdateStatus::ItemUpdateStatusInvalid;
	}
	uint64 BytesProcessed64;
	uint64 BytesTotal64;
	EItemUpdateStatus Status = SteamUGC()->GetItemUpdateProgress(UpdateHandle.GetUGCUpdateHandle(), &BytesProcessed64, &BytesTotal64);
	BytesProcessed = BytesProcessed64;
	BytesTotal = BytesTotal64;
	return static_cast<ESIK_ItemUpdateStatus>(Status);
}

int32 USIK_UGCLibrary::GetNumSubscribedItems()
{
	if(!SteamUGC())
	{
		return 0;
	}
	return SteamUGC()->GetNumSubscribedItems();
}

bool USIK_UGCLibrary::GetQueryUGCAdditionalPreview(FSIK_UGCQueryHandle QueryHandle,int32 Index, int32 PreviewIndex,
	FString& PreviewURL, FString& OriginalFileName, TEnumAsByte<ESIK_ItemPreviewType>& FileType)
{
	if(!SteamUGC())
	{
		return false;
	}
	char PreviewURLBuffer[1024];
	char OriginalFileNameBuffer[1024];
	EItemPreviewType FileTypeValue;
	bool bResult = SteamUGC()->GetQueryUGCAdditionalPreview(QueryHandle.GetUGCQueryHandle(),Index, PreviewIndex, PreviewURLBuffer, 1024, OriginalFileNameBuffer, 1024, &FileTypeValue);
	PreviewURL = FString(UTF8_TO_TCHAR(PreviewURLBuffer));
	OriginalFileName = FString(UTF8_TO_TCHAR(OriginalFileNameBuffer));
	FileType = static_cast<ESIK_ItemPreviewType>(FileTypeValue);
	return bResult;
}

bool USIK_UGCLibrary::GetQueryUGCChildren(FSIK_UGCQueryHandle QueryHandle, int32 Index,
	TArray<FSIK_PublishedFileId>& PublishedFileIDs, int32 MaxEntries)
{
	if(!SteamUGC())
	{
		return false;
	}
	PublishedFileId_t PublishedFileIDsArray[50];
	bool NumEntries = SteamUGC()->GetQueryUGCChildren(QueryHandle.GetUGCQueryHandle(), Index, PublishedFileIDsArray, MaxEntries);
	for(int32 i = 0; i < MaxEntries; i++)
	{
		PublishedFileIDs.Add(FSIK_PublishedFileId(PublishedFileIDsArray[i]));
	}
	return NumEntries;
}

int32 USIK_UGCLibrary::GetQueryUGCNumTags(FSIK_UGCQueryHandle QueryHandle, int32 Index)
{
	if(!SteamUGC())
	{
		return 0;
	}
	return SteamUGC()->GetQueryUGCNumTags(QueryHandle.GetUGCQueryHandle(), Index);
}

bool USIK_UGCLibrary::GetQueryUGCTag(FSIK_UGCQueryHandle QueryHandle, int32 Index, int32 TagIndex, FString& TagName)
{
	if(!SteamUGC())
	{
		return false;
	}
	char TagNameBuffer[1024];
	bool bResult = SteamUGC()->GetQueryUGCTag(QueryHandle.GetUGCQueryHandle(), Index, TagIndex, TagNameBuffer, 1024);
	TagName = FString(UTF8_TO_TCHAR(TagNameBuffer));
	return bResult;
}

bool USIK_UGCLibrary::GetQueryUGCTagDisplayName(FSIK_UGCQueryHandle QueryHandle, int32 Index, int32 TagIndex,
	FString& TagName)
{
	if(!SteamUGC())
	{
		return false;
	}
	char TagNameBuffer[1024];
	bool bResult = SteamUGC()->GetQueryUGCTagDisplayName(QueryHandle.GetUGCQueryHandle(), Index, TagIndex, TagNameBuffer, 1024);
	TagName = FString(UTF8_TO_TCHAR(TagNameBuffer));
	return bResult;
}

bool USIK_UGCLibrary::GetQueryUGCKeyValueTag(FSIK_UGCQueryHandle QueryHandle, int32 Index, const FString& Key,
	FString& Value)
{
	if(!SteamUGC())
	{
		return false;
	}
	char ValueBuffer[1024];
	bool bResult = SteamUGC()->GetQueryUGCKeyValueTag(QueryHandle.GetUGCQueryHandle(), Index, TCHAR_TO_UTF8(*Key), ValueBuffer, 1024);
	Value = FString(UTF8_TO_TCHAR(ValueBuffer));
	return bResult;
}

int32 USIK_UGCLibrary::GetQueryUGCContentDescriptors(FSIK_UGCQueryHandle QueryHandle, int32 Index,
	TArray<TEnumAsByte<ESIK_UGCContentDescriptorID>>& ContentDescriptors, int32 MaxEntries)
{
	if(!SteamUGC())
	{
		return 0;
	}
#if WITH_ENGINE_STEAM
	return 0;
#else
	EUGCContentDescriptorID ContentDescriptorsArray[50];
	int32 NumEntries = SteamUGC()->GetQueryUGCContentDescriptors(QueryHandle.GetUGCQueryHandle(), Index, ContentDescriptorsArray, MaxEntries);
	for(int32 i = 0; i < NumEntries; i++)
	{
		ContentDescriptors.Add(static_cast<ESIK_UGCContentDescriptorID>(ContentDescriptorsArray[i]));
	}
	return NumEntries;
#endif
}

bool USIK_UGCLibrary::GetQueryUGCMetadata(FSIK_UGCQueryHandle QueryHandle, int32 Index, FString& Metadata)
{
	if(!SteamUGC())
	{
		return false;
	}
	char MetadataBuffer[1024];
	bool bResult = SteamUGC()->GetQueryUGCMetadata(QueryHandle.GetUGCQueryHandle(), Index, MetadataBuffer, 1024);
	Metadata = FString(UTF8_TO_TCHAR(MetadataBuffer));
	return bResult;
}

int32 USIK_UGCLibrary::GetQueryUGCNumAdditionalPreviews(FSIK_UGCQueryHandle QueryHandle, int32 Index)
{
	if(!SteamUGC())
	{
		return 0;
	}
	return SteamUGC()->GetQueryUGCNumAdditionalPreviews(QueryHandle.GetUGCQueryHandle(), Index);
}

int32 USIK_UGCLibrary::GetQueryUGCNumKeyValueTags(FSIK_UGCQueryHandle QueryHandle, int32 Index)
{
	if(!SteamUGC())
	{
		return 0;
	}
	return SteamUGC()->GetQueryUGCNumKeyValueTags(QueryHandle.GetUGCQueryHandle(), Index);
}

bool USIK_UGCLibrary::GetQueryUGCPreviewURL(FSIK_UGCQueryHandle QueryHandle, int32 Index, FString& URL)
{
	if(!SteamUGC())
	{
		return false;
	}
	char URLBuffer[1024];
	bool bResult = SteamUGC()->GetQueryUGCPreviewURL(QueryHandle.GetUGCQueryHandle(), Index, URLBuffer, 1024);
	URL = FString(UTF8_TO_TCHAR(URLBuffer));
	return bResult;
}

bool USIK_UGCLibrary::GetQueryUGCResult(FSIK_UGCQueryHandle QueryHandle, int32 Index, FSIK_SteamUGCDetails& Details)
{
	if(!SteamUGC())
	{
		return false;
	}
	SteamUGCDetails_t SteamDetails;
	bool bResult = SteamUGC()->GetQueryUGCResult(QueryHandle.GetUGCQueryHandle(), Index, &SteamDetails);
	Details = SteamDetails;
	return bResult;
}

bool USIK_UGCLibrary::GetQueryUGCStatistic(FSIK_UGCQueryHandle QueryHandle, int32 Index,
	TEnumAsByte<ESIK_ItemStatistic> StatType, int64& Value)
{
	if(!SteamUGC())
	{
		return false;
	}
	uint64 Value64;
	bool bResult = SteamUGC()->GetQueryUGCStatistic(QueryHandle.GetUGCQueryHandle(), Index, static_cast<EItemStatistic>(StatType.GetValue()), &Value64);
	Value = Value64;
	return bResult;
}

int32 USIK_UGCLibrary::GetSubscribedItems(TArray<FSIK_PublishedFileId>& PublishedFileIDs, int32 MaxEntries)
{
	if(!SteamUGC())
	{
		return 0;
	}
	PublishedFileId_t PublishedFileIDsArray[50];
	int32 NumEntries = SteamUGC()->GetSubscribedItems(PublishedFileIDsArray, MaxEntries);
	for(int32 i = 0; i < NumEntries; i++)
	{
		PublishedFileIDs.Add(FSIK_PublishedFileId(PublishedFileIDsArray[i]));
	}
	return NumEntries;
}

bool USIK_UGCLibrary::ReleaseQueryUGCRequest(FSIK_UGCQueryHandle QueryHandle)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->ReleaseQueryUGCRequest(QueryHandle.GetUGCQueryHandle());
}

bool USIK_UGCLibrary::RemoveItemKeyValueTags(FSIK_UGCUpdateHandle UpdateHandle, const FString& Key)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->RemoveItemKeyValueTags(UpdateHandle.GetUGCUpdateHandle(), TCHAR_TO_UTF8(*Key));
}

bool USIK_UGCLibrary::RemoveItemPreview(FSIK_UGCUpdateHandle UpdateHandle, int32 PreviewIndex)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->RemoveItemPreview(UpdateHandle.GetUGCUpdateHandle(), PreviewIndex);
}

bool USIK_UGCLibrary::AddContentDescriptor(FSIK_UGCUpdateHandle UpdateHandle,
	TEnumAsByte<ESIK_UGCContentDescriptorID> ContentDescriptor)
{
	if(!SteamUGC())
	{
		return false;
	}
#if !WITH_ENGINE_STEAM
	return SteamUGC()->AddContentDescriptor(UpdateHandle.GetUGCUpdateHandle(), static_cast<EUGCContentDescriptorID>(ContentDescriptor.GetValue()));
#else
	return false;
#endif
}

bool USIK_UGCLibrary::RemoveContentDescriptor(FSIK_UGCUpdateHandle UpdateHandle,
	TEnumAsByte<ESIK_UGCContentDescriptorID> ContentDescriptor)
{
	if(!SteamUGC())
	{
		return false;
	}
#if !WITH_ENGINE_STEAM
	return SteamUGC()->RemoveContentDescriptor(UpdateHandle.GetUGCUpdateHandle(), static_cast<EUGCContentDescriptorID>(ContentDescriptor.GetValue()));
#else
	return false;
#endif
}

bool USIK_UGCLibrary::SetAllowCachedResponse(FSIK_UGCQueryHandle QueryHandle, int32 MaxAgeSeconds)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->SetAllowCachedResponse(QueryHandle.GetUGCQueryHandle(), MaxAgeSeconds);
}

bool USIK_UGCLibrary::SetCloudFileNameFilter(FSIK_UGCQueryHandle QueryHandle, const FString& MatchCloudFileName)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->SetCloudFileNameFilter(QueryHandle.GetUGCQueryHandle(), TCHAR_TO_UTF8(*MatchCloudFileName));
}

bool USIK_UGCLibrary::SetItemContent(FSIK_UGCUpdateHandle UpdateHandle, const FString& Content)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->SetItemContent(UpdateHandle.GetUGCUpdateHandle(), TCHAR_TO_UTF8(*Content));
}

bool USIK_UGCLibrary::SetItemDescription(FSIK_UGCUpdateHandle UpdateHandle, const FString& Description)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->SetItemDescription(UpdateHandle.GetUGCUpdateHandle(), TCHAR_TO_UTF8(*Description));
}	

bool USIK_UGCLibrary::SetItemMetadata(FSIK_UGCUpdateHandle UpdateHandle, const FString& Metadata)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->SetItemMetadata(UpdateHandle.GetUGCUpdateHandle(), TCHAR_TO_UTF8(*Metadata));
}

bool USIK_UGCLibrary::SetItemPreview(FSIK_UGCUpdateHandle UpdateHandle, const FString& PreviewFile)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->SetItemPreview(UpdateHandle.GetUGCUpdateHandle(), TCHAR_TO_UTF8(*PreviewFile));
}
bool USIK_UGCLibrary::SetItemTags(FSIK_UGCUpdateHandle UpdateHandle, const TArray<FString>& Tags)
{
	if(!SteamUGC())
	{
		return false;
	}
	SteamParamStringArray_t* ParamArray = new SteamParamStringArray_t();
	TArray<const char*> TagsArray;
	for(const FString& Tag : Tags)
	{
		TagsArray.Add(TCHAR_TO_UTF8(*Tag));
	}
	ParamArray->m_ppStrings = TagsArray.GetData();
	ParamArray->m_nNumStrings = TagsArray.Num();
	return SteamUGC()->SetItemTags(UpdateHandle.GetUGCUpdateHandle(), ParamArray);
}

bool USIK_UGCLibrary::SetItemTitle(FSIK_UGCUpdateHandle UpdateHandle, const FString& Title)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->SetItemTitle(UpdateHandle.GetUGCUpdateHandle(), TCHAR_TO_UTF8(*Title));
}

bool USIK_UGCLibrary::SetItemUpdateLanguage(FSIK_UGCUpdateHandle UpdateHandle, const FString& Language)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->SetItemUpdateLanguage(UpdateHandle.GetUGCUpdateHandle(), TCHAR_TO_UTF8(*Language));
}

bool USIK_UGCLibrary::SetItemVisibility(FSIK_UGCUpdateHandle UpdateHandle,
	TEnumAsByte<ESIK_RemoteStoragePublishedFileVisibility> Visibility)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->SetItemVisibility(UpdateHandle.GetUGCUpdateHandle(), static_cast<ERemoteStoragePublishedFileVisibility>(Visibility.GetValue()));
}

bool USIK_UGCLibrary::SetLanguage(FSIK_UGCQueryHandle QueryHandle, const FString& Language)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->SetLanguage(QueryHandle.GetUGCQueryHandle(), TCHAR_TO_UTF8(*Language));
}

bool USIK_UGCLibrary::SetMatchAnyTag(FSIK_UGCQueryHandle QueryHandle, bool bMatchAnyTag)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->SetMatchAnyTag(QueryHandle.GetUGCQueryHandle(), bMatchAnyTag);
}

bool USIK_UGCLibrary::SetRankedByTrendDays(FSIK_UGCQueryHandle QueryHandle, int32 Days)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->SetRankedByTrendDays(QueryHandle.GetUGCQueryHandle(), Days);
}

bool USIK_UGCLibrary::SetReturnAdditionalPreviews(FSIK_UGCQueryHandle QueryHandle, bool bReturnAdditionalPreviews)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->SetReturnAdditionalPreviews(QueryHandle.GetUGCQueryHandle(), bReturnAdditionalPreviews);
}

bool USIK_UGCLibrary::SetReturnChildren(FSIK_UGCQueryHandle QueryHandle, bool bReturnChildren)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->SetReturnChildren(QueryHandle.GetUGCQueryHandle(), bReturnChildren);
}

bool USIK_UGCLibrary::SetReturnKeyValueTags(FSIK_UGCQueryHandle QueryHandle, bool bReturnKeyValueTags)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->SetReturnKeyValueTags(QueryHandle.GetUGCQueryHandle(), bReturnKeyValueTags);
}

bool USIK_UGCLibrary::SetReturnLongDescription(FSIK_UGCQueryHandle QueryHandle, bool bReturnLongDescription)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->SetReturnLongDescription(QueryHandle.GetUGCQueryHandle(), bReturnLongDescription);
}

bool USIK_UGCLibrary::SetReturnMetadata(FSIK_UGCQueryHandle QueryHandle, bool bReturnMetadata)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->SetReturnMetadata(QueryHandle.GetUGCQueryHandle(), bReturnMetadata);
}

bool USIK_UGCLibrary::SetReturnOnlyIDs(FSIK_UGCQueryHandle QueryHandle, bool bReturnOnlyIDs)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->SetReturnOnlyIDs(QueryHandle.GetUGCQueryHandle(), bReturnOnlyIDs);
}

bool USIK_UGCLibrary::SetReturnPlaytimeStats(FSIK_UGCQueryHandle QueryHandle, int32 Days)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->SetReturnPlaytimeStats(QueryHandle.GetUGCQueryHandle(), Days);
}

bool USIK_UGCLibrary::SetReturnTotalOnly(FSIK_UGCQueryHandle QueryHandle, bool bReturnTotalOnly)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->SetReturnTotalOnly(QueryHandle.GetUGCQueryHandle(), bReturnTotalOnly);
}

bool USIK_UGCLibrary::SetSearchText(FSIK_UGCQueryHandle QueryHandle, const FString& SearchText)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->SetSearchText(QueryHandle.GetUGCQueryHandle(), TCHAR_TO_UTF8(*SearchText));
}

bool USIK_UGCLibrary::SetUserItemVote(FSIK_PublishedFileId PublishedFileId, bool bVoteUp)
{
	if(!SteamUGC())
	{
		return false;
	}
	SteamUGC()->SetUserItemVote(PublishedFileId.GetPublishedFileId(), bVoteUp);
	return true;
}

FSIK_UGCUpdateHandle USIK_UGCLibrary::StartItemUpdate(FSIK_AppId AppID, FSIK_PublishedFileId PublishedFileID)
{
	if(!SteamUGC())
	{
		return FSIK_UGCUpdateHandle();
	}
	return SteamUGC()->StartItemUpdate(AppID.GetAppID(), PublishedFileID.GetPublishedFileId());
}

void USIK_UGCLibrary::SuspendDownloads(bool bSuspend)
{
	if(!SteamUGC())
	{
		return;
	}
	SteamUGC()->SuspendDownloads(bSuspend);
}

bool USIK_UGCLibrary::UpdateItemPreviewFile(FSIK_UGCUpdateHandle UpdateHandle, int32 PreviewIndex,
	const FString& PreviewFile)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->UpdateItemPreviewFile(UpdateHandle.GetUGCUpdateHandle(), PreviewIndex, TCHAR_TO_UTF8(*PreviewFile));
}

bool USIK_UGCLibrary::UpdateItemPreviewVideo(FSIK_UGCUpdateHandle UpdateHandle, int32 PreviewIndex,
	const FString& VideoID)
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->UpdateItemPreviewVideo(UpdateHandle.GetUGCUpdateHandle(), PreviewIndex, TCHAR_TO_UTF8(*VideoID));
}

bool USIK_UGCLibrary::ShowWorkshopEULA()
{
	if(!SteamUGC())
	{
		return false;
	}
	return SteamUGC()->ShowWorkshopEULA();
}