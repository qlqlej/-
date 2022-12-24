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
	class UTextBlock* coin_name;  // �����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* purchase_price;  // ���԰�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* aluation_profitand_loss;  // �� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_rate;  // ���ͷ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* amount;  // ���� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_price;  // ���簡

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* purchase_amount;  // ���� �ݾ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* evaluated_price;  // �� �ݾ�

protected:
	virtual void NativeConstruct() override;  // ������

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;  // ������ UI ������ ȣ��

	virtual void NativeOnItemSelectionChanged(bool blsSelected) override;  // ������ ���ý� ȣ��

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