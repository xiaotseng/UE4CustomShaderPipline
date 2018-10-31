#pragma once

/* <�ڵ����ݽṹ */

#include "DDFileTreeItem.h"
#include "SlateCore.h"
#include "Slate.h"


typedef STreeView< FDDFileTreeItemPtr > SDDFileTreeView;

/**
* <Ŀ¼��Slate
*/

class ZLJSLATE_API SDDFileTree : public SCompoundWidget
{

public:
	//����ܹ�ͨ��SNew����Swidget�Ĵ���
	//���¶�����һ���ṹ�������� void Construct(const FArguments& InArgs) ���ܵĲ�������
	//{}�����ǹ��캯����
	SLATE_BEGIN_ARGS(SDDFileTree) {}
	SLATE_ARGUMENT(TWeakObjectPtr<class AHUD>, OwnerHUD);
	//��Ӵ������
	SLATE_END_ARGS()
	

public:

	TWeakObjectPtr<AHUD> OwnerHUD;//�����ĸ�HUD

	/** <ˢ��Ŀ¼ */

	//bool DoRefresh;

public:

	void Construct(const FArguments& InArgs);
	

	/** Destructor */
	~SDDFileTree();

	/** @return <���ص�ǰ��ѡ�е�Ŀ¼ */
	FDDFileTreeItemPtr GetSelectedDirectory() const;

	/** <ѡ��Ŀ¼ */
	void SelectDirectory(const FDDFileTreeItemPtr& CategoryToSelect);

	/** @return <���ؽڵ��Ƿ�չ�� */
	bool IsItemExpanded(const FDDFileTreeItemPtr Item) const;

private:

	/** <���ɵ����ڵ�Ԫ�� */
	TSharedRef<ITableRow> DDFileTree_OnGenerateRow(FDDFileTreeItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable);

	/** <����ӽڵ� */
	void DDFileTree_OnGetChildren(FDDFileTreeItemPtr Item, TArray< FDDFileTreeItemPtr >& OutChildren);

	/** <��ѡ������仯ʱ */
	void DDFileTree_OnSelectionChanged(FDDFileTreeItemPtr Item, ESelectInfo::Type SelectInfo);

	/** <����Ŀ¼������ */
	void RebuildFileTree();

	/** <��дTick�����Ժ�ʵ��Ŀ¼ˢ�� */
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

private:

	/** <TreeView�ؼ� */
	TSharedPtr< SDDFileTreeView > DDFileTreeView;

	/** <Ŀ¼�������� */
	TArray< FDDFileTreeItemPtr > Directories;

};