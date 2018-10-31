#include "FrontPage.h"
void SFrontPage::Construct(const FArguments &InArgs)
{
	ChildSlot[
		SNew(SButton)[
			SNew(STextBlock).Text(FText::FromString("kele"))
		]
	];
	

}

SFrontPage::SFrontPage()
{

}

