#pragma once
#include "EngineMinimal.h"

typedef TSharedPtr< class FDDFileTreeItem > FDDFileTreeItemPtr;

/**
* <目录树节点
*/

class FDDFileTreeItem
{
public:

	/** @return <返回父节点 */
	const FDDFileTreeItemPtr GetParentCategory() const
	{
		return ParentDir.Pin();
	}

	/** @return <返回节点的路径【只读】 */
	const FString& GetDirectoryPath() const
	{
		return DirectoryPath;
	}

	/** @return <返回显示名称【只读】 */
	const FString& GetDisplayName() const
	{
		return DisplayName;
	}

	/** @return <返回子节点【只读】 */
	const TArray< FDDFileTreeItemPtr >& GetSubDirectories() const
	{
		return SubDirectories;
	}

	/** @return <返回可写入的子节点引用 */
	TArray< FDDFileTreeItemPtr >& AccessSubDirectories()
	{
		return SubDirectories;
	}

	/** <为当前节点添加子目录 */
	void AddSubDirectory(const FDDFileTreeItemPtr NewSubDir)
	{
		SubDirectories.Add(NewSubDir);
	}

public:
	/** <构造函数 */

	FDDFileTreeItem(const FDDFileTreeItemPtr IN_ParentDir, const FString& IN_DirectoryPath, const FString& IN_DisplayName)
		: ParentDir(IN_ParentDir)
		, DirectoryPath(IN_DirectoryPath)
		, DisplayName(IN_DisplayName)
	{

	}

private:

	/** <父节点引用; */
	TWeakPtr< FDDFileTreeItem > ParentDir;

	/** <完整路径 */
	FString DirectoryPath;

	/** <显示名称 */
	FString DisplayName;

	/** <子节点数组 */
	TArray< FDDFileTreeItemPtr > SubDirectories;

};