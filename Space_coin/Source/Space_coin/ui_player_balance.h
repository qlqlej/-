#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "ui_player_balance.generated.h"

UCLASS()
class SPACE_COIN_API Uui_player_balance : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* purchase;  // �Ѹ���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* evaluation;  // ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* profit_and_loss;  // �Ѽ���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* rate;  // �Ѽ��ͷ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* realized_profit_and_loss;  // ��������

protected:
	virtual void NativeConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetPurchase(int32 set_purchase);
	void SetEvaluation(int32 set_evaluation);
	void SetProfitAndLoss(int32 set_profit_and_loss);
	void SetRate(float set_rate);
	void SetRealizedProfitAndLoss(int32 set_realized_profit_and_loss);
	
};
