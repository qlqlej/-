#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ui_coin_price.generated.h"

UCLASS()
class SPACE_COIN_API Uui_coin_price : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_name;  // �����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_price;  // �ü�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_fluctate_24H;  // �����ݾ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_fluctate_rate_24H;  // ������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_acc_trade_value_24H;  // �ŷ��ݾ�

	class Udata_coin_price* data;

protected:
	virtual void NativeConstruct() override;  // ������

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;  // ������ UI ������ ȣ��

	virtual void NativeOnItemSelectionChanged(bool blsSelected) override;  // ������ ���ý� ȣ��

public:
	void SetCoinName(const FString& name);
	void SetCoinPrice(int32 price);
	void SetCoinFluctate24H(int32 price);
	void SetCoinFluctateRate24H(float rate);
	void SetCoinAccTradeValue24H(float value);

public:
	UFUNCTION(BlueprintCallable)
	void SetData(class Udata_coin_price* data);

};
