#include "ui_quest.h"
#include "Components/TextBlock.h"
#include "game_instance.h"

void Uui_quest::NativeConstruct()
{
	Super::NativeConstruct();

	quest_text = Cast<UTextBlock>(GetWidgetFromName(TEXT("quest_text")));
	clear_quest_text = Cast<UTextBlock>(GetWidgetFromName(TEXT("clear_quest_text")));

	GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));

	quest_level = -1;
	quest_goal_rate = 0;
	quest_now_rate = 0;
}

void Uui_quest::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	quest_level = GameInstanceRef->quest_level;
	quest_now_rate = GameInstanceRef->quest_now_rate;
	quest_goal_rate = GameInstanceRef->quest_goal_rate;

	FStringFormatOrderedArguments args;
	args.Add(quest_now_rate);
	args.Add(quest_goal_rate);

	switch (quest_level)
	{
	case 0:
		str_q = FString::Format(TEXT("퀘스트1.\r행성으로 이동 후 우주선에서 내리기"), args);
		text_q = FText::FromString(str_q);
		quest_text->SetColorAndOpacity(FSlateColor(FColor::Black));
		quest_text->SetText(text_q);

		str_cq = FString::Format(TEXT("완료된 퀘스트가 없습니다."), args);
		text_cq = FText::FromString(str_cq);
		clear_quest_text->SetColorAndOpacity(FSlateColor(FColor::Black));
		clear_quest_text->SetText(text_cq);
		break;
	case 1:
		str_q = FString::Format(TEXT("퀘스트2.\r몬스터 10마리 사냥\r({0} / {1})"), args);
		text_q = FText::FromString(str_q);
		quest_text->SetColorAndOpacity(FSlateColor(FColor::Black));
		quest_text->SetText(text_q);

		str_cq = FString::Format(TEXT("퀘스트1. 행성으로 이동 후 우주선에서 내리기"), args);
		text_cq = FText::FromString(str_cq);
		clear_quest_text->SetColorAndOpacity(FSlateColor(FColor::Black));
		clear_quest_text->SetText(text_cq);
		break;
	case 2:
		str_q = FString::Format(TEXT("퀘스트3.\r코인 판매하기"), args);
		text_q = FText::FromString(str_q);
		quest_text->SetColorAndOpacity(FSlateColor(FColor::Black));
		quest_text->SetText(text_q);

		str_cq = FString::Format(TEXT("퀘스트1. 행성으로 이동 후 우주선에서 내리기\r퀘스트2. 몬스터 10마리 사냥"), args);
		text_cq = FText::FromString(str_cq);
		clear_quest_text->SetColorAndOpacity(FSlateColor(FColor::Black));
		clear_quest_text->SetText(text_cq);
		break;
	case 3:
		str_q = FString::Format(TEXT("퀘스트4.\r코인 구입하기"), args);
		text_q = FText::FromString(str_q);
		quest_text->SetColorAndOpacity(FSlateColor(FColor::Black));
		quest_text->SetText(text_q);

		str_cq = FString::Format(TEXT("퀘스트1. 행성으로 이동 후 우주선에서 내리기\r퀘스트2. 몬스터 10마리 사냥\r퀘스트3. 코인 판매하기"), args);
		text_cq = FText::FromString(str_cq);
		clear_quest_text->SetColorAndOpacity(FSlateColor(FColor::Black));
		clear_quest_text->SetText(text_cq);
		break;
	case 4:
		str_q = FString::Format(TEXT("퀘스트5.\r아이템 구입하기"), args);
		text_q = FText::FromString(str_q);
		quest_text->SetColorAndOpacity(FSlateColor(FColor::Black));
		quest_text->SetText(text_q);

		str_cq = FString::Format(TEXT("퀘스트1. 행성으로 이동 후 우주선에서 내리기\r퀘스트2. 몬스터 10마리 사냥\r퀘스트3. 코인 판매하기\r퀘스트4. 코인 구입하기"), args);
		text_cq = FText::FromString(str_cq);
		clear_quest_text->SetColorAndOpacity(FSlateColor(FColor::Black));
		clear_quest_text->SetText(text_cq);
		break;
	case 5:
		str_q = FString::Format(TEXT("퀘스트6.\r코인으로 이익보기\r({0} / {1})"), args);
		text_q = FText::FromString(str_q);
		quest_text->SetColorAndOpacity(FSlateColor(FColor::Black));
		quest_text->SetText(text_q);

		str_cq = FString::Format(TEXT("퀘스트1. 행성으로 이동 후 우주선에서 내리기\r퀘스트2. 몬스터 10마리 사냥\r퀘스트3. 코인 판매하기\r퀘스트4. 코인 구입하기\r퀘스트5. 아이템 구입하기"), args);
		text_cq = FText::FromString(str_cq);
		clear_quest_text->SetColorAndOpacity(FSlateColor(FColor::Black));
		clear_quest_text->SetText(text_cq);
		break;
	case -1:
		str_q = FString::Format(TEXT("진행 중인 퀘스트가 없습니다."), args);
		text_q = FText::FromString(str_q);
		quest_text->SetColorAndOpacity(FSlateColor(FColor::Black));
		quest_text->SetText(text_q);

		str_cq = FString::Format(TEXT("완료된 퀘스트가 없습니다."), args);
		text_cq = FText::FromString(str_cq);
		clear_quest_text->SetColorAndOpacity(FSlateColor(FColor::Black));
		clear_quest_text->SetText(text_cq);
		break;
	default:
		str_q = FString::Format(TEXT("진행 중인 퀘스트가 없습니다."), args);
		text_q = FText::FromString(str_q);
		quest_text->SetColorAndOpacity(FSlateColor(FColor::Black));
		quest_text->SetText(text_q);

		str_cq = FString::Format(TEXT("퀘스트1. 행성으로 이동 후 우주선에서 내리기\r퀘스트2. 몬스터 10마리 사냥\r퀘스트3. 코인 판매하기\r퀘스트4. 코인 구입하기\r퀘스트5. 아이템 구입하기\r퀘스트6. 코인으로 이익보기"), args);
		text_cq = FText::FromString(str_cq);
		clear_quest_text->SetColorAndOpacity(FSlateColor(FColor::Black));
		clear_quest_text->SetText(text_cq);
		break;
	}
}
