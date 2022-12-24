#include "ui_coin_fail_or_success.h"
#include "Components/TextBlock.h"

void Uui_coin_fail_or_success::NativeConstruct()
{
	Super::NativeConstruct();

	TextBlock_text = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_text")));
	text_num = 0;

	name = "xxx";
	amount = -1;
	price = -1;
}

void Uui_coin_fail_or_success::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	FStringFormatOrderedArguments args;
	args.Add(name);
	args.Add(amount);
	args.Add(price);

	switch (text_num)
	{
	case 1:
		str = FString::Format(TEXT("stock : {0} amount : {1} price : {2}\rBuy Succeed"), args);
		text = FText::FromString(str);
		TextBlock_text->SetText(text);
		break;
	case 2:
		str = FString::Format(TEXT("stock : {0} amount : {1} price : {2}\rBuy Fail"), args);
		text = FText::FromString(str);
		TextBlock_text->SetText(text);
		break;
	case 3:
		str = FString::Format(TEXT("stock : {0} amount : {1} price : {2}\rSell Succeed"), args);
		text = FText::FromString(str);
		TextBlock_text->SetText(text);
		break;
	case 4:
		str = FString::Format(TEXT("stock : {0} amount : {1} price : {2}\rSell Fail"), args);
		text = FText::FromString(str);
		TextBlock_text->SetText(text);
		break;
	default:
		str = FString(TEXT("000"));
		text = FText::FromString(str);
		TextBlock_text->SetText(text);
		break;
	}
}