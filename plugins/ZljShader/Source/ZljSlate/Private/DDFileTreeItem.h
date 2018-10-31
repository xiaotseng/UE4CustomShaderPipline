#pragma once
#include "EngineMinimal.h"

typedef TSharedPtr< class FDDFileTreeItem > FDDFileTreeItemPtr;

/**
* <Ŀ¼���ڵ�
*/

class FDDFileTreeItem
{
public:

	/** @return <���ظ��ڵ� */
	const FDDFileTreeItemPtr GetParentCategory() const
	{
		return ParentDir.Pin();
	}

	/** @return <���ؽڵ��·����ֻ���� */
	const FString& GetDirectoryPath() const
	{
		return DirectoryPath;
	}

	/** @return <������ʾ���ơ�ֻ���� */
	const FString& GetDisplayName() const
	{
		return DisplayName;
	}

	/** @return <�����ӽڵ㡾ֻ���� */
	const TArray< FDDFileTreeItemPtr >& GetSubDirectories() const
	{
		return SubDirectories;
	}

	/** @return <���ؿ�д����ӽڵ����� */
	TArray< FDDFileTreeItemPtr >& AccessSubDirectories()
	{
		return SubDirectories;
	}

	/** <Ϊ��ǰ�ڵ������Ŀ¼ */
	void AddSubDirectory(const FDDFileTreeItemPtr NewSubDir)
	{
		SubDirectories.Add(NewSubDir);
	}

public:
	/** <���캯�� */

	FDDFileTreeItem(const FDDFileTreeItemPtr IN_ParentDir, const FString& IN_DirectoryPath, const FString& IN_DisplayName)
		: ParentDir(IN_ParentDir)
		, DirectoryPath(IN_DirectoryPath)
		, DisplayName(IN_DisplayName)
	{

	}

private:

	/** <���ڵ�����; */
	TWeakPtr< FDDFileTreeItem > ParentDir;

	/** <����·�� */
	FString DirectoryPath;

	/** <��ʾ���� */
	FString DisplayName;

	/** <�ӽڵ����� */
	TArray< FDDFileTreeItemPtr > SubDirectories;

};