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
	class UTextBlock* coin_name;  // 종목명

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_price;  // 시세

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_fluctate_24H;  // 변동금액

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_fluctate_rate_24H;  // 변동률

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_acc_trade_value_24H;  // 거래금액

	class Udata_coin_price* data;

protected:
	virtual void NativeConstruct() override;  // 생성자

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;  // 아이템 UI 설정시 호출

	virtual void NativeOnItemSelectionChanged(bool blsSelected) override;  // 아이템 선택시 호출

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
