﻿// Copyright 2021. Ashot Barkhudaryan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetData.h"
#include "StructsContainer.generated.h"

class ICleanerUIActions
{
public:
	virtual ~ICleanerUIActions() {}
	
	virtual void ExcludeSelectedAssets(const TArray<FAssetData>& Assets) = 0;
	virtual void ExcludeSelectedAssetsByType(const TArray<FAssetData>& Assets) = 0;
	virtual bool IncludeSelectedAssets(const TArray<FAssetData>& Assets) = 0;
	virtual void IncludeAllAssets() = 0;
	virtual bool ExcludePath(const FString& InPath) = 0;
	virtual bool IncludePath(const FString& InPath) = 0;
	virtual int32 DeleteSelectedAssets(const TArray<FAssetData>& Assets) = 0;
	virtual int32 DeleteAllUnusedAssets() = 0;
	virtual int32 DeleteEmptyFolders() = 0;
};

UCLASS(Transient)
class UCleanerConfigs : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(DisplayName = "Scan Developer Content", EditAnywhere, Category = "CleanerConfigs", meta = (ToolTip = "Scan assets in 'Developers' folder. By Default false"))
	bool bScanDeveloperContents = false;

	UPROPERTY(DisplayName = "Delete Empty Folders After Assets Deleted", EditAnywhere, Category = "CleanerConfigs")
	bool bAutomaticallyDeleteEmptyFolders = true;
	
	UPROPERTY(DisplayName = "Paths", EditAnywhere, Category = "CleanerConfigs|ExcludeOptions", meta = (ContentDir))
	TArray<FDirectoryPath> Paths;

	UPROPERTY(DisplayName = "Classes", EditAnywhere, Category = "CleanerConfigs|ExcludeOptions")
	TArray<UClass*> Classes;
};

UCLASS(Transient)
class UIndirectAsset : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(DisplayName = "AssetName", VisibleAnywhere, Category="AssetUsedIndirectly")
	FString AssetName;

	UPROPERTY(DisplayName = "AssetPath", VisibleAnywhere, Category="AssetUsedIndirectly")
	FString AssetPath;

	UPROPERTY(DisplayName = "FilePath where asset used", VisibleAnywhere, Category="AssetUsedIndirectly")
	FString FilePath;

	UPROPERTY(DisplayName = "Line where asset used", VisibleAnywhere, Category="AssetUsedIndirectly")
	int32 LineNum;

	UPROPERTY(DisplayName = "AssetData", VisibleAnywhere, Category="AssetUsedIndirectly")
	FAssetData AssetData;
};

UCLASS(Transient)
class UCorruptedFile : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(DisplayName = "Name", VisibleAnywhere, Category = "CorruptedFile")
	FString Name;
	UPROPERTY(DisplayName = "AbsolutePath", VisibleAnywhere, Category = "CorruptedFile")
	FString AbsolutePath;
};

UCLASS(Transient)
class UNonEngineFile : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(DisplayName = "FileName", VisibleAnywhere, Category = "NonEngineFile")
	FString FileName;

	UPROPERTY(DisplayName = "FilePath", VisibleAnywhere, Category = "NonEngineFile")
	FString FilePath;
};

struct FIndirectAsset
{
	FString File;
	int32 Line;
	FName RelativePath;

	FIndirectAsset(): File(FString{}), Line(0), RelativePath(NAME_None) {}
};

struct FStandardCleanerText
{
	inline const static TCHAR* AssetsDeleteWindowTitle = TEXT("Confirm deletion");
	inline const static TCHAR* AssetsDeleteWindowContent = TEXT("Are you sure you want to permanently delete unused assets?");
	inline const static TCHAR* EmptyFolderWindowTitle = TEXT("Confirm deletion of empty folders");
	inline const static TCHAR* EmptyFolderWindowContent = TEXT("Are you sure you want to delete all empty folders in project?");
	inline const static TCHAR* DeletingUnusedAssets = TEXT("Deleting unused assets...");
	inline const static TCHAR* DeletingEmptyFolders = TEXT("Deleting empty folders...");
	inline const static TCHAR* NoAssetsToDelete = TEXT("There are no assets to delete!");
	inline const static TCHAR* NoEmptyFolderToDelete = TEXT("There are no empty folders to delete!");
	inline const static TCHAR* AssetRegistryStillWorking = TEXT("Please wait, AssetRegistry is loading assets");
	inline const static TCHAR* CantIncludeSomeAssets = TEXT("Cant include selected assets, because they are excluded by 'Exclude Options' filter.");
	inline const static TCHAR* CantIncludePath = TEXT("Cant include selected path, because they are excluded by 'Exclude Options' filter.");
	inline const static TCHAR* FailedToDeleteSomeFolders = TEXT("Failed to delete some folders. Open 'Output Log' for more information.");
	inline const static TCHAR* FailedToDeleteSomeAssets = TEXT("Failed to delete some assets");
	inline const static TCHAR* SearchingForUnusedAssets = TEXT("Searching for unused assets...");
	inline const static TCHAR* Scanning = TEXT("Scanning...");
	inline const static TCHAR* UnusedAssetsSuccessfullyDeleted = TEXT("Unused assets deleted successfully");
	inline const static TCHAR* FoldersSuccessfullyDeleted = TEXT("Empty folders deleted successfully");
	inline const static TCHAR* LoadingAssets = TEXT("Loading assets...");
	inline const static TCHAR* FixingUpRedirectors = TEXT("Fixing up redirectors...");
	inline const static TCHAR* AnalyzingAssets = TEXT("Analyzing unused assets...");
	inline const static TCHAR* PreparingAssetsForDeletion = TEXT("Preparing assets for deletion...");
	inline const static TCHAR* RestartEditorTitle = TEXT("Confirm Restart Editor");
	inline const static TCHAR* RestartEditorContent = TEXT("To finish project cleaning,its recommended to Restart Editor. Proceed?");
};