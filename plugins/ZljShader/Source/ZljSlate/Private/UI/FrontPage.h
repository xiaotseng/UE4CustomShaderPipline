#pragma once
#include"Slate.h"
#include "SlateCore.h"
class SFrontPage:public SCompoundWidget
{
	//{}��ṹ��Ĺ��캯��
	SLATE_BEGIN_ARGS(SFrontPage) {}
	//�������ṹ������ݳ�Ա
	SLATE_ARGUMENT(TWeakObjectPtr<class AHUD>, OnwerHUD);
	SLATE_ARGUMENT(TWeakObjectPtr<class AActor>, TestActor);

	SLATE_END_ARGS()
	
public:
	void Construct(const FArguments &InArgs);
	SFrontPage();
	~SFrontPage() {}
private:

};
