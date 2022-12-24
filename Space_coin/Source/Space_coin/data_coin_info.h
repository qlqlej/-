#pragma once

#include "game_info.h"
#include "UObject/NoExportTypes.h"
#include "data_coin_info.generated.h"

UCLASS()
class SPACE_COIN_API Udata_coin_info : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FString coin_name;  // 종목명

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 coin_price;  // 시세

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float coin_units_traded_24H;  // 거래량(24H)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float coin_acc_trade_value_24H;  // 거래금액(24H)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 coin_max_price;  // 고가(당일)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 coin_min_price;  //  저가(당일)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 coin_fluctate_rate_24H;  // 변동률

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float coin_prev_closing_price;  // 전일종가

public:
	FString GetCoinName() const
	{
		return coin_name;
	}

	int32 GetCoinPrice() const
	{
		return coin_price;
	}

	float GetCoinUnitsTraded24H() const
	{
		return coin_units_traded_24H;
	}

	float GetCoinAccTradeValue24H() const
	{
		return coin_acc_trade_value_24H;
	}

	int32 GetCoinMaxPrice() const
	{
		return coin_max_price;
	}

	int32 GetCoinMinPrice() const
	{
		return coin_min_price;
	}

	int32 GetCoinFluctateRate24H() const
	{
		return coin_fluctate_rate_24H;
	}

	float GetCoinPrevClosingPrice() const
	{
		return coin_prev_closing_price;
	}


	void SetCoinName(FString name)
	{
		coin_name = name;
	}

	void SetCoinPrice(int32 price)
	{
		coin_price = price;
	}

	void SetCoinUnitsTraded24H(float amount)
	{
		coin_units_traded_24H = amount;
	}

	void SetCoinAccTradeValue24H(float value)
	{
		coin_acc_trade_value_24H = value;
	}

	void SetCoinMaxPrice(int32 price)
	{
		coin_max_price = price;
	}

	void SetCoinMinPrice(int32 price)
	{
		coin_min_price = price;
	}

	void SetCoinFluctateRate24H(int32 volatility)
	{
		coin_fluctate_rate_24H = volatility;
	}

	void SetCoinPrevClosingPrice(float price)
	{
		coin_prev_closing_price = price;
	}
};

