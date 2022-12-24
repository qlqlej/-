#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cstring>
#include "includePython.h"
using namespace std;

void main()
{
	CoinAPI coinapi;
	coinapi.GetCoinAPI();
}

/* 종목명 및 정보 */
void CoinAPI::GetCoinAPI()
{
	Py_Initialize();

	pName = PyUnicode_FromString("SpaceCoin_CoinAPI"); // xxx.py를 PyObject로 생성
	pModule = PyImport_Import(pName); // 생성한 PyObject pName을 import
	pFunc = PyObject_GetAttrString(pModule, "requestCoinAPI"); // 실행할 함수를 PyObject에 전달 
	pValue = PyObject_CallObject(pFunc, NULL); // pFunc에 매개변수를 전달해서 실행. 현재 매개변수가 NULL인 경우

	coin_name = GetCoinName();  // 이름
	opening_price = GetOpeningPrice();  // 시가 00시 기준
	closing_price = GetClosingPrice();  // 종가 00시 기준 현재가격
	min_price = GetMinPrice();  // 저가 00시 기준
	max_price = GetMaxPrice();  // 고가 00시 기준
	units_traded = GetUnitsTraded();  // 거래량 00시 기준
	prev_closing_price = GetPrevClosingPrice();  // 거래금액 00시 기준
	acc_trade_value = GetAccTradeValue();  // 전일종가
	units_traded_24H = GetUnitsTraded24H();  // 최근 24시간 거래량
	acc_trade_value_24H = GetAccTradeValue24H();  // 최근 24시간 거래금액
	fluctate_24H = GetFluctate24H();  // 최근 24시간 변동가
	fluctate_rate_24H = GetFluctateRate24H();  // 최근 24시간 변동률*/
}

vector<string> CoinAPI::GetCoinName()
{
	cout << "GetCoinName" << endl;

	int count = 10;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 0);

		objectsRepresentation = PyObject_Repr(item); // 객체를 문자열로 표현
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // 객체를 인코딩
		return_val = PyBytes_AsString(str); // string으로 변환하여 줌

		cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetOpeningPrice()
{
	cout << endl << "GetOpeningPrice" << endl;

	int count = 10;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 1);

		objectsRepresentation = PyObject_Repr(item); // 객체를 문자열로 표현
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // 객체를 인코딩
		return_val = PyBytes_AsString(str); // string으로 변환하여 줌
		
		cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetClosingPrice()
{
	cout << endl << "GetClosingPrice" << endl;

	int count = 10;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 2);

		objectsRepresentation = PyObject_Repr(item); // 객체를 문자열로 표현
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // 객체를 인코딩
		return_val = PyBytes_AsString(str); // string으로 변환하여 줌

		cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetMinPrice()
{
	cout << endl << "GetMinPrice" << endl;

	int count = 10;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 3);

		objectsRepresentation = PyObject_Repr(item); // 객체를 문자열로 표현
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // 객체를 인코딩
		return_val = PyBytes_AsString(str); // string으로 변환하여 줌

		cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetMaxPrice()
{
	cout << endl << "GetMaxPrice" << endl;

	int count = 10;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 4);

		objectsRepresentation = PyObject_Repr(item); // 객체를 문자열로 표현
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // 객체를 인코딩
		return_val = PyBytes_AsString(str); // string으로 변환하여 줌

		cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetUnitsTraded()
{
	cout << endl << "GetUnitsTraded" << endl;

	int count = 10;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 5);

		objectsRepresentation = PyObject_Repr(item); // 객체를 문자열로 표현
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // 객체를 인코딩
		return_val = PyBytes_AsString(str); // string으로 변환하여 줌

		cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetPrevClosingPrice()
{
	cout << endl << "GetPrevClosingPrice" << endl;

	int count = 10;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 6);

		objectsRepresentation = PyObject_Repr(item); // 객체를 문자열로 표현
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // 객체를 인코딩
		return_val = PyBytes_AsString(str); // string으로 변환하여 줌

		cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetAccTradeValue()
{
	cout << endl << "GetAccTradeValue" << endl;

	int count = 10;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 7);

		objectsRepresentation = PyObject_Repr(item); // 객체를 문자열로 표현
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // 객체를 인코딩
		return_val = PyBytes_AsString(str); // string으로 변환하여 줌

		cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetUnitsTraded24H()
{
	cout << endl << "GetUnitsTraded24H" << endl;

	int count = 10;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 8);

		objectsRepresentation = PyObject_Repr(item); // 객체를 문자열로 표현
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // 객체를 인코딩
		return_val = PyBytes_AsString(str); // string으로 변환하여 줌

		cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetAccTradeValue24H()
{
	cout << endl << "GetAccTradeValue24H" << endl;

	int count = 10;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 9);

		objectsRepresentation = PyObject_Repr(item); // 객체를 문자열로 표현
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // 객체를 인코딩
		return_val = PyBytes_AsString(str); // string으로 변환하여 줌

		cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetFluctate24H()
{
	cout << endl << "GetFluctate24H" << endl;

	int count = 10;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 10);

		objectsRepresentation = PyObject_Repr(item); // 객체를 문자열로 표현
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // 객체를 인코딩
		return_val = PyBytes_AsString(str); // string으로 변환하여 줌

		cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetFluctateRate24H()
{
	cout << endl << "GetFluctateRate24H" << endl;

	int count = 10;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 11);

		objectsRepresentation = PyObject_Repr(item); // 객체를 문자열로 표현
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // 객체를 인코딩
		return_val = PyBytes_AsString(str); // string으로 변환하여 줌

		cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

/*
	print("시가 00시 기준 : ", info['opening_price'])
	print("종가 00시 기준 : ", info['closing_price'])
	print("저가 00시 기준 : ", info['min_price'])
	print("고가 00시 기준 : ", info['max_price'])
	print("거래량 00시 기준 : ", info['units_traded'])
	print("거래금액 00시 기준 : ", info['prev_closing_price'])
	print("전일종가 : ", info['acc_trade_value'])
	print("최근 24시간 거래량 : ", info['units_traded_24H'])
	print("최근 24시간 거래금액 : ", info['acc_trade_value_24H'])
	print("최근 24시간 변동가 : ", info['fluctate_24H'])
	print("최근 24시간 변동률 : ", info['fluctate_rate_24H'])
	*/

/* 종목명 */
/*void CoinAPI::StockSymbol()
{
	PyObject* pName, * pModule, * pFunc, * pValue, * objectsRepresentation;

	Py_Initialize();

	pName = PyUnicode_FromString("SpaceCoin_CoinAPI"); // xxx.py를 PyObject로 생성
	pModule = PyImport_Import(pName); // 생성한 PyObject pName을 import
	pFunc = PyObject_GetAttrString(pModule, "requestStockSymbols"); // 실행할 함수를 PyObject에 전달 
	pValue = PyObject_CallObject(pFunc, NULL); // pFunc에 매개변수를 전달해서 실행. 현재 매개변수가 NULL인 경우

	int count = 201;
	vector<string> stock_symbols(count);  // 배열 저장할 vector 생성
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int low = i;
		int high = i + 1;
		PyObject* p = PyList_GetSlice(pValue, low, high);
		objectsRepresentation = PyObject_Repr(p); // 객체를 문자열로 표현
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // 객체를 인코딩
		return_val = PyBytes_AsString(str); // string으로 변환하여 줌
		stock_symbols[i] = return_val;
		cout << stock_symbols[i] << endl;
	}
}*/

/* 종목 정보 */
/*void CoinAPI::StockInfo(string stock_symbol, string field)
{
	PyObject* pName, * pModule, * pFunc, * pValue, * objectsRepresentation;

	Py_Initialize();

	//string stock_symbol = "BTC";
	//string field = "opening_price";

	char* c_stock_symbol = new char[stock_symbol.length() + 1];
	std::strcpy(c_stock_symbol, stock_symbol.c_str());

	char* c_field = new char[field.length() + 1];
	std::strcpy(c_field, field.c_str());

	pName = PyUnicode_FromString("SpaceCoin_CoinAPI"); // xxx.py를 PyObject로 생성
	pModule = PyImport_Import(pName); // 생성한 PyObject pName을 import
	pFunc = PyObject_GetAttrString(pModule, "requestInfo"); // 실행할 함수를 PyObject에 전달 
	PyObject* pArgs = PyTuple_New(2);
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", c_stock_symbol));
	PyTuple_SetItem(pArgs, 1, Py_BuildValue("s", c_field));
	pValue = PyObject_CallObject(pFunc, pArgs); // pFunc에 매개변수를 전달해서 실행

	objectsRepresentation = PyObject_Repr(pValue); // 객체를 문자열로 표현
	PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // 객체를 인코딩
	string result = PyBytes_AsString(str); // string으로 변환하여 줌
	cout << result;

	/*
	print("시가 00시 기준 : ", info['opening_price'])
	print("종가 00시 기준 : ", info['closing_price'])
	print("저가 00시 기준 : ", info['min_price'])
	print("고가 00시 기준 : ", info['max_price'])
	print("거래량 00시 기준 : ", info['units_traded'])
	print("거래금액 00시 기준 : ", info['prev_closing_price'])
	print("전일종가 : ", info['acc_trade_value'])
	print("최근 24시간 거래량 : ", info['units_traded_24H'])
	print("최근 24시간 거래금액 : ", info['acc_trade_value_24H'])
	print("최근 24시간 변동가 : ", info['fluctate_24H'])
	print("최근 24시간 변동률 : ", info['fluctate_rate_24H'])
	*/

	//Py_Finalize();
//}


/* 매개변수와 return 값이 없는 함수 */
/*pName = PyUnicode_FromString("SpaceCoin_CoinAPI"); // xxx.py를 PyObject로 생성
pModule = PyImport_Import(pName); // 생성한 PyObject pName을 import
pFunc = PyObject_GetAttrString(pModule, "requestTicker"); // 실행할 함수를 PyObject에 전달
pValue = PyObject_CallObject(pFunc, NULL); // pFunc에 매개변수를 전달해서 실행. 현재 매개변수가 NULL인 경우*/

/* 문자열 매개변수와 string형 return 값이 있는 함수 */
/*pName = PyUnicode_FromString("SpaceCoin_CoinAPI"); // xxx.py를 PyObject로 생성
pModule = PyImport_Import(pName); // 생성한 PyObject pName을 import
pFunc = PyObject_GetAttrString(pModule, "test_func"); // 실행할 함수를 PyObject에 전달
pArg = Py_BuildValue("(z)", (const char*)"hello"); // 문자열 hello를 담은 매개변수를 만듦
pValue = PyObject_CallObject(pFunc, pArg); // pFunc에 매개변수를 전달해서 실행

PyObject* objectsRepresentation = PyObject_Repr(pValue); // 객체를 문자열로 표현
PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // 객체를 인코딩
string result = PyBytes_AsString(str); // string으로 변환하여 줌
cout << result;*/

/* int형 매개변수와 int형 배열 return 값이 있는 함수 */
/*pName = PyUnicode_FromString("SpaceCoin_CoinAPI"); // xxx.py를 PyObject로 생성
pModule = PyImport_Import(pName); // 생성한 PyObject pName을 import
pFunc = PyObject_GetAttrString(pModule, "test_func"); // 실행할 함수를 PyObject에 전달
pArg = Py_BuildValue("(i, i, i, i)", 1, 2, 3, 4); // int형 인자 4개를 전달
pValue = PyObject_CallObject(pFunc, pArg); // pFunc에 매개변수를 전달해서 실행

int count = (int)PyList_Size(pValue); // count 변수에 함수에서 반환된 배열의 size를 전달
vector<int> arr(count); // 배열을 저장할 vector 생성
const char* return_val;

for (int i = 0; i < count; i++)
{
	ptemp = PyList_GetItem(pValue, i);
	objectsRepresentation = PyObject_Repr(ptemp);
	PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~");
	return_val = PyBytes_AsString(str);
	arr[i] = (float)strtod(return_val, NULL);
	cout << arr[i] << " ";
}*/