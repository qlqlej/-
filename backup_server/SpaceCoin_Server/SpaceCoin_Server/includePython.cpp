#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cstring>
#include "includePython.h"
using namespace std;

void CoinAPI::GetCoinAPI()
{
	Py_Initialize();

	pName = PyUnicode_FromString("SpaceCoin_CoinAPI");
	pModule = PyImport_Import(pName);
	pFunc = PyObject_GetAttrString(pModule, "requestCoinAPI");
	pValue = PyObject_CallObject(pFunc, NULL);

	coin_name = GetCoinName();
	opening_price = GetOpeningPrice();
	closing_price = GetClosingPrice();
	min_price = GetMinPrice();
	max_price = GetMaxPrice();
	units_traded = GetUnitsTraded();
	prev_closing_price = GetPrevClosingPrice();
	acc_trade_value = GetAccTradeValue();
	units_traded_24H = GetUnitsTraded24H();
	acc_trade_value_24H = GetAccTradeValue24H();
	fluctate_24H = GetFluctate24H();
	fluctate_rate_24H = GetFluctateRate24H();

	Py_Finalize();
}

vector<string> CoinAPI::GetCoinName()
{
	//cout << "GetCoinName" << endl;

	int count = 3;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 0);

		objectsRepresentation = PyObject_Repr(item);
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~");
		return_val = PyBytes_AsString(str);

		//cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetOpeningPrice()
{
	//cout << endl << "GetOpeningPrice" << endl;

	int count = 3;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 1);

		objectsRepresentation = PyObject_Repr(item);
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~");
		return_val = PyBytes_AsString(str);

		//cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetClosingPrice()
{
	//cout << endl << "GetClosingPrice" << endl;

	int count = 3;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 2);

		objectsRepresentation = PyObject_Repr(item);
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~");
		return_val = PyBytes_AsString(str);

		//cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetMinPrice()
{
	//cout << endl << "GetMinPrice" << endl;

	int count = 3;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 3);

		objectsRepresentation = PyObject_Repr(item);
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~");
		return_val = PyBytes_AsString(str);

		//cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetMaxPrice()
{
	//cout << endl << "GetMaxPrice" << endl;

	int count = 3;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 4);

		objectsRepresentation = PyObject_Repr(item);
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~");
		return_val = PyBytes_AsString(str);

		//cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetUnitsTraded()
{
	//cout << endl << "GetUnitsTraded" << endl;

	int count = 3;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 5);

		objectsRepresentation = PyObject_Repr(item);
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~");
		return_val = PyBytes_AsString(str);

		//cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetPrevClosingPrice()
{
	//cout << endl << "GetPrevClosingPrice" << endl;

	int count = 3;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 6);

		objectsRepresentation = PyObject_Repr(item);
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~");
		return_val = PyBytes_AsString(str);

		//cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetAccTradeValue()
{
	//cout << endl << "GetAccTradeValue" << endl;

	int count = 3;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 7);

		objectsRepresentation = PyObject_Repr(item);
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~");
		return_val = PyBytes_AsString(str);

		//cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetUnitsTraded24H()
{
	//cout << endl << "GetUnitsTraded24H" << endl;

	int count = 3;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 8);

		objectsRepresentation = PyObject_Repr(item);
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~");
		return_val = PyBytes_AsString(str);

		//cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetAccTradeValue24H()
{
	//cout << endl << "GetAccTradeValue24H" << endl;

	int count = 3;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 9);

		objectsRepresentation = PyObject_Repr(item);
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~");
		return_val = PyBytes_AsString(str);

		//cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetFluctate24H()
{
	//cout << endl << "GetFluctate24H" << endl;

	int count = 3;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 10);

		objectsRepresentation = PyObject_Repr(item);
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~");
		return_val = PyBytes_AsString(str);

		//cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

vector<string> CoinAPI::GetFluctateRate24H()
{
	//cout << endl << "GetFluctateRate24H" << endl;

	int count = 3;
	vector<string> data;
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int iLow = i;  // 0
		int iHigh = i + 1;  // 1

		PyObject* lists = PyList_GetSlice(pValue, iLow, iHigh);
		PyObject* list = PyList_GetItem(lists, 0);
		PyObject* item = PyList_GetItem(list, 11);

		objectsRepresentation = PyObject_Repr(item);
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~");
		return_val = PyBytes_AsString(str);

		//cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}