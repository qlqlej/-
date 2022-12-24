#include "ui_player_holdings.h"
#include "Components/ListView.h"
#include "data_player_holding_coin.h"
#include "MyCharacter.h"
#include "MainGamePlayerController.h"
#include "game_instance.h"

void Uui_player_holdings::NativeConstruct()
{
	Super::NativeConstruct();

	player_holding_list_view = Cast<UListView>(GetWidgetFromName(TEXT("player_holding_list_view")));

	player_holding_list_view->OnItemClicked().AddUObject(this, &Uui_player_holdings::ItemClick);

	player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	pc = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	InitList();
}

void Uui_player_holdings::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void Uui_player_holdings::InitList()
{
	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));

	switch (GameInstanceRef->mycharacter_type)
	{
	case CHARACTER_TYPE::HUMAN:
	{
		AMyCharacter* my_character = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (my_character->a_coin > 0) {
			Udata_player_holding_coin* a_data = NewObject<Udata_player_holding_coin>(this, Udata_player_holding_coin::StaticClass());

			a_data->SetCoinName(pc->a_coin.coin_name);  // �̸�
			a_data->SetPurchasePrice(468413511);  // ���԰�
			a_data->SetAluationProfitandLoss(86.2);  // �򰡼���
			a_data->SetCoinRate(1666);  // ���ͷ�
			a_data->SetAmount(my_character->a_coin);  // ��������
			a_data->SetPurchaseAmount(pc->a_coin.closing_price);  // ���簡
			a_data->SetCoinPrice(pc->a_coin.closing_price);  // ���Աݾ�
			a_data->SetEvaluatedPrice(1666);  // �򰡱ݾ�

			player_holding_list_view->AddItem(a_data);
		}

		if (my_character->b_coin > 0) {
			Udata_player_holding_coin* b_data = NewObject<Udata_player_holding_coin>(this, Udata_player_holding_coin::StaticClass());

			b_data->SetCoinName(pc->b_coin.coin_name);  // �̸�
			b_data->SetPurchasePrice(468413511);  // ���԰�
			b_data->SetAluationProfitandLoss(86.2);  // �򰡼���
			b_data->SetCoinRate(1666);  // ���ͷ�
			b_data->SetAmount(my_character->b_coin);  // ��������
			b_data->SetPurchaseAmount(pc->b_coin.closing_price);  // ���簡
			b_data->SetCoinPrice(pc->b_coin.closing_price);  // ���Աݾ�
			b_data->SetEvaluatedPrice(1666);  // �򰡱ݾ�

			player_holding_list_view->AddItem(b_data);
		}

		if (my_character->c_coin > 0) {
			Udata_player_holding_coin* c_data = NewObject<Udata_player_holding_coin>(this, Udata_player_holding_coin::StaticClass());

			c_data->SetCoinName(pc->c_coin.coin_name);  // �̸�
			c_data->SetPurchasePrice(468413511);  // ���԰�
			c_data->SetAluationProfitandLoss(86.2);  // �򰡼���
			c_data->SetCoinRate(1666);  // ���ͷ�
			c_data->SetAmount(my_character->c_coin);  // ��������
			c_data->SetPurchaseAmount(pc->c_coin.closing_price);  // ���簡
			c_data->SetCoinPrice(pc->a_coin.closing_price);  // ���Աݾ�
			c_data->SetEvaluatedPrice(1666);  // �򰡱ݾ�

			player_holding_list_view->AddItem(c_data);
		}
		break;
	}
	case CHARACTER_TYPE::SPACESHIP:
	{
		Aspace_ship* ship = Cast<Aspace_ship>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (ship->owner_character->a_coin > 0) {
			Udata_player_holding_coin* a_data = NewObject<Udata_player_holding_coin>(this, Udata_player_holding_coin::StaticClass());

			a_data->SetCoinName(pc->a_coin.coin_name);  // �̸�
			a_data->SetPurchasePrice(468413511);  // ���԰�
			a_data->SetAluationProfitandLoss(86.2);  // �򰡼���
			a_data->SetCoinRate(1666);  // ���ͷ�
			a_data->SetAmount(ship->owner_character->a_coin);  // ��������
			a_data->SetPurchaseAmount(pc->a_coin.closing_price);  // ���簡
			a_data->SetCoinPrice(pc->a_coin.closing_price);  // ���Աݾ�
			a_data->SetEvaluatedPrice(1666);  // �򰡱ݾ�

			player_holding_list_view->AddItem(a_data);
		}

		if (ship->owner_character->b_coin > 0) {
			Udata_player_holding_coin* b_data = NewObject<Udata_player_holding_coin>(this, Udata_player_holding_coin::StaticClass());

			b_data->SetCoinName(pc->b_coin.coin_name);  // �̸�
			b_data->SetPurchasePrice(468413511);  // ���԰�
			b_data->SetAluationProfitandLoss(86.2);  // �򰡼���
			b_data->SetCoinRate(1666);  // ���ͷ�
			b_data->SetAmount(ship->owner_character->b_coin);  // ��������
			b_data->SetPurchaseAmount(pc->b_coin.closing_price);  // ���簡
			b_data->SetCoinPrice(pc->b_coin.closing_price);  // ���Աݾ�
			b_data->SetEvaluatedPrice(1666);  // �򰡱ݾ�

			player_holding_list_view->AddItem(b_data);
		}

		if (ship->owner_character->c_coin > 0) {
			Udata_player_holding_coin* c_data = NewObject<Udata_player_holding_coin>(this, Udata_player_holding_coin::StaticClass());

			c_data->SetCoinName(pc->c_coin.coin_name);  // �̸�
			c_data->SetPurchasePrice(468413511);  // ���԰�
			c_data->SetAluationProfitandLoss(86.2);  // �򰡼���
			c_data->SetCoinRate(1666);  // ���ͷ�
			c_data->SetAmount(ship->owner_character->c_coin);  // ��������
			c_data->SetPurchaseAmount(pc->c_coin.closing_price);  // ���簡
			c_data->SetCoinPrice(pc->a_coin.closing_price);  // ���Աݾ�
			c_data->SetEvaluatedPrice(1666);  // �򰡱ݾ�

			player_holding_list_view->AddItem(c_data);
		}
		break;
	}
	default:
		break;
	}

}

void Uui_player_holdings::SetData()
{
	player_holding_list_view->ClearListItems();
	InitList();
}

void Uui_player_holdings::ItemClick(UObject* obj)
{
}