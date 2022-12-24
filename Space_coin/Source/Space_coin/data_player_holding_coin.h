#pragma once

#include "game_info.h"
#include "UObject/NoExportTypes.h"
#include "data_player_holding_coin.generated.h"

UCLASS()
class SPACE_COIN_API Udata_player_holding_coin : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FString coin_name;  // 종목명

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 purchase_price;  // 매입가

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float aluation_profitand_loss;  // 평가 손익

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float coin_rate;  // 손익률

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 amount;  // 보유 수량

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 coin_price;  // 현재가

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 purchase_amount;  // 매입 금액

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 evaluated_price;  // 평가 금액

public:
	FString GetCoinName() const
	{
		return coin_name;
	}

	int32 GetPurchasePrice() const
	{
		return purchase_price;
	}

	float GetAluationProfitandLoss() const
	{
		return aluation_profitand_loss;
	}

	float GetCoinRate() const
	{
		return coin_rate;
	}

	int32 GetAmount() const
	{
		return amount;
	}

	int32 GetCoinPrice() const
	{
		return coin_price;
	}

	int32 GetPurchaseAmount() const
	{
		return purchase_amount;
	}

	int32 GetEvaluatedPrice() const
	{
		return evaluated_price;
	}

	void SetCoinName(FString name)
	{
		coin_name = name;
	}

	void SetPurchasePrice(int32 price)
	{
		purchase_price = price;
	}

	void SetAluationProfitandLoss(float profitand_loss)
	{
		aluation_profitand_loss = profitand_loss;
	}

	void SetCoinRate(float rate)
	{
		coin_rate = rate;
	}

	void SetAmount(int32 amt)
	{
		amount = amt;
	}

	void SetCoinPrice(int32 price)
	{
		coin_price = price;
	}

	void SetPurchaseAmount(int32 amt)
	{
		purchase_amount = amt;
	}

	void SetEvaluatedPrice(int32 price)
	{
		evaluated_price = price;
	}

};
