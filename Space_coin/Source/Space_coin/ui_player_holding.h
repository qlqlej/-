#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ui_player_holding.generated.h"

UCLASS()
class SPACE_COIN_API Uui_player_holding : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_name;  // 종목명

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* purchase_price;  // 매입가

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* aluation_profitand_loss;  // 평가 손익

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_rate;  // 손익률

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* amount;  // 보유 수량

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_price;  // 현재가

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* purchase_amount;  // 매입 금액

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* evaluated_price;  // 평가 금액

protected:
	virtual void NativeConstruct() override;  // 생성자

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;  // 아이템 UI 설정시 호출

	virtual void NativeOnItemSelectionChanged(bool blsSelected) override;  // 아이템 선택시 호출

public:
	void SetCoinName(const FString& name);
	void SetPurchasePrice(int32 price);
	void SetAluationProfitandLoss(float profitand_loss);
	void SetCoinRate(float rate);
	void SetAmount(int32 amt);
	void SetCoinPrice(int32 price);
	void SetPurchaseAmount(int32 amt);
	void SetEvaluatedPrice(int32 price);

public:
	UFUNCTION(BlueprintCallable)
	void SetData(class Udata_player_holding_coin* data);

};