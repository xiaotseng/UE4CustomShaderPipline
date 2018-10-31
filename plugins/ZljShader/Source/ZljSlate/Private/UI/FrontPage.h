#pragma once
#include"Slate.h"
#include "SlateCore.h"
class SFrontPage:public SCompoundWidget
{
	//{}里结构体的构造函数
	SLATE_BEGIN_ARGS(SFrontPage) {}
	//这里放入结构体的数据成员
	SLATE_ARGUMENT(TWeakObjectPtr<class AHUD>, OnwerHUD);
	SLATE_ARGUMENT(TWeakObjectPtr<class AActor>, TestActor);

	SLATE_END_ARGS()
	
public:
	void Construct(const FArguments &InArgs);
	SFrontPage();
	~SFrontPage() {}
private:

};
