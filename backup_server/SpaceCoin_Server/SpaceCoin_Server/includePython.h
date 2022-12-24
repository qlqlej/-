#ifdef _DEBUG
#define _DEBUG_WAS_DEFINED 1
#undef _DEBUG
#endif
#include "include/Python.h"
#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG 1
#endif

#define UNICODE
#include <string>
#pragma comment (lib, "python39.lib")
#pragma comment (lib, "python3.lib")
using namespace std;

class CoinAPI {
public:
	PyObject* pName, * pModule, * pFunc, * pValue, * objectsRepresentation;

	vector<string> coin_name;  // 이름
	vector<string> opening_price;  // 시가 00시 기준
	vector<string> closing_price;  // 종가 00시 기준
	vector<string> min_price;  // 저가 00시 기준
	vector<string> max_price;  // 고가 00시 기준
	vector<string> units_traded;  // 거래량 00시 기준
	vector<string> prev_closing_price;  // 거래금액 00시 기준
	vector<string> acc_trade_value;  // 전일종가
	vector<string> units_traded_24H;  // 최근 24시간 거래량
	vector<string> acc_trade_value_24H;  // 최근 24시간 거래금액
	vector<string> fluctate_24H;  // 최근 24시간 변동가
	vector<string> fluctate_rate_24H;  // 최근 24시간 변동률

public:
	void GetCoinAPI();

	vector<string> GetCoinName();
	vector<string> GetOpeningPrice();
	vector<string> GetClosingPrice();
	vector<string> GetMinPrice();
	vector<string> GetMaxPrice();
	vector<string> GetUnitsTraded();
	vector<string> GetPrevClosingPrice();
	vector<string> GetAccTradeValue();
	vector<string> GetUnitsTraded24H();
	vector<string> GetAccTradeValue24H();
	vector<string> GetFluctate24H();
	vector<string> GetFluctateRate24H();
};