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

	vector<string> coin_name;  // �̸�
	vector<string> opening_price;  // �ð� 00�� ����
	vector<string> closing_price;  // ���� 00�� ����
	vector<string> min_price;  // ���� 00�� ����
	vector<string> max_price;  // �� 00�� ����
	vector<string> units_traded;  // �ŷ��� 00�� ����
	vector<string> prev_closing_price;  // �ŷ��ݾ� 00�� ����
	vector<string> acc_trade_value;  // ��������
	vector<string> units_traded_24H;  // �ֱ� 24�ð� �ŷ���
	vector<string> acc_trade_value_24H;  // �ֱ� 24�ð� �ŷ��ݾ�
	vector<string> fluctate_24H;  // �ֱ� 24�ð� ������
	vector<string> fluctate_rate_24H;  // �ֱ� 24�ð� ������

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