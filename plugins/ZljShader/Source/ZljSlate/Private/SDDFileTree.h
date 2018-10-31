#pragma once

/* <节点数据结构 */

#include "DDFileTreeItem.h"
#include "SlateCore.h"
#include "Slate.h"


typedef STreeView< FDDFileTreeItemPtr > SDDFileTreeView;

/**
* <目录树Slate
*/

class ZLJSLATE_API SDDFileTree : public SCompoundWidget
{

public:
	//添加能够通过SNew构造Swidget的代码
	//以下定义了一个结构，是用于 void Construct(const FArguments& InArgs) 接受的参数类型
	//{}里面是构造函数体
	SLATE_BEGIN_ARGS(SDDFileTree) {}
	SLATE_ARGUMENT(TWeakObjectPtr<class AHUD>, OwnerHUD);
	//添加代码结束
	SLATE_END_ARGS()
	

public:

	TWeakObjectPtr<AHUD> OwnerHUD;//属于哪个HUD

	/** <刷新目录 */

	//bool DoRefresh;

public:

	void Construct(const FArguments& InArgs);
	

	/** Destructor */
	~SDDFileTree();

	/** @return <返回当前被选中的目录 */
	FDDFileTreeItemPtr GetSelectedDirectory() const;

	/** <选择目录 */
	void SelectDirectory(const FDDFileTreeItemPtr& CategoryToSelect);

	/** @return <返回节点是否展开 */
	bool IsItemExpanded(const FDDFileTreeItemPtr Item) const;

private:

	/** <生成单个节点元素 */
	TSharedRef<ITableRow> DDFileTree_OnGenerateRow(FDDFileTreeItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable);

	/** <获得子节点 */
	void DDFileTree_OnGetChildren(FDDFileTreeItemPtr Item, TArray< FDDFileTreeItemPtr >& OutChildren);

	/** <当选中项发生变化时 */
	void DDFileTree_OnSelectionChanged(FDDFileTreeItemPtr Item, ESelectInfo::Type SelectInfo);

	/** <构建目录树数据 */
	void RebuildFileTree();

	/** <重写Tick方便以后实现目录刷新 */
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

private:

	/** <TreeView控件 */
	TSharedPtr< SDDFileTreeView > DDFileTreeView;

	/** <目录树的数据 */
	TArray< FDDFileTreeItemPtr > Directories;

};