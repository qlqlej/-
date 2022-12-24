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

/* ����� �� ���� */
void CoinAPI::GetCoinAPI()
{
	Py_Initialize();

	pName = PyUnicode_FromString("SpaceCoin_CoinAPI"); // xxx.py�� PyObject�� ����
	pModule = PyImport_Import(pName); // ������ PyObject pName�� import
	pFunc = PyObject_GetAttrString(pModule, "requestCoinAPI"); // ������ �Լ��� PyObject�� ���� 
	pValue = PyObject_CallObject(pFunc, NULL); // pFunc�� �Ű������� �����ؼ� ����. ���� �Ű������� NULL�� ���

	coin_name = GetCoinName();  // �̸�
	opening_price = GetOpeningPrice();  // �ð� 00�� ����
	closing_price = GetClosingPrice();  // ���� 00�� ���� ���簡��
	min_price = GetMinPrice();  // ���� 00�� ����
	max_price = GetMaxPrice();  // �� 00�� ����
	units_traded = GetUnitsTraded();  // �ŷ��� 00�� ����
	prev_closing_price = GetPrevClosingPrice();  // �ŷ��ݾ� 00�� ����
	acc_trade_value = GetAccTradeValue();  // ��������
	units_traded_24H = GetUnitsTraded24H();  // �ֱ� 24�ð� �ŷ���
	acc_trade_value_24H = GetAccTradeValue24H();  // �ֱ� 24�ð� �ŷ��ݾ�
	fluctate_24H = GetFluctate24H();  // �ֱ� 24�ð� ������
	fluctate_rate_24H = GetFluctateRate24H();  // �ֱ� 24�ð� ������*/
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

		objectsRepresentation = PyObject_Repr(item); // ��ü�� ���ڿ��� ǥ��
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // ��ü�� ���ڵ�
		return_val = PyBytes_AsString(str); // string���� ��ȯ�Ͽ� ��

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

		objectsRepresentation = PyObject_Repr(item); // ��ü�� ���ڿ��� ǥ��
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // ��ü�� ���ڵ�
		return_val = PyBytes_AsString(str); // string���� ��ȯ�Ͽ� ��
		
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

		objectsRepresentation = PyObject_Repr(item); // ��ü�� ���ڿ��� ǥ��
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // ��ü�� ���ڵ�
		return_val = PyBytes_AsString(str); // string���� ��ȯ�Ͽ� ��

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

		objectsRepresentation = PyObject_Repr(item); // ��ü�� ���ڿ��� ǥ��
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // ��ü�� ���ڵ�
		return_val = PyBytes_AsString(str); // string���� ��ȯ�Ͽ� ��

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

		objectsRepresentation = PyObject_Repr(item); // ��ü�� ���ڿ��� ǥ��
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // ��ü�� ���ڵ�
		return_val = PyBytes_AsString(str); // string���� ��ȯ�Ͽ� ��

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

		objectsRepresentation = PyObject_Repr(item); // ��ü�� ���ڿ��� ǥ��
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // ��ü�� ���ڵ�
		return_val = PyBytes_AsString(str); // string���� ��ȯ�Ͽ� ��

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

		objectsRepresentation = PyObject_Repr(item); // ��ü�� ���ڿ��� ǥ��
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // ��ü�� ���ڵ�
		return_val = PyBytes_AsString(str); // string���� ��ȯ�Ͽ� ��

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

		objectsRepresentation = PyObject_Repr(item); // ��ü�� ���ڿ��� ǥ��
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // ��ü�� ���ڵ�
		return_val = PyBytes_AsString(str); // string���� ��ȯ�Ͽ� ��

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

		objectsRepresentation = PyObject_Repr(item); // ��ü�� ���ڿ��� ǥ��
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // ��ü�� ���ڵ�
		return_val = PyBytes_AsString(str); // string���� ��ȯ�Ͽ� ��

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

		objectsRepresentation = PyObject_Repr(item); // ��ü�� ���ڿ��� ǥ��
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // ��ü�� ���ڵ�
		return_val = PyBytes_AsString(str); // string���� ��ȯ�Ͽ� ��

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

		objectsRepresentation = PyObject_Repr(item); // ��ü�� ���ڿ��� ǥ��
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // ��ü�� ���ڵ�
		return_val = PyBytes_AsString(str); // string���� ��ȯ�Ͽ� ��

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

		objectsRepresentation = PyObject_Repr(item); // ��ü�� ���ڿ��� ǥ��
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // ��ü�� ���ڵ�
		return_val = PyBytes_AsString(str); // string���� ��ȯ�Ͽ� ��

		cout << return_val << " ";

		data.push_back(return_val);
	}

	return data;
}

/*
	print("�ð� 00�� ���� : ", info['opening_price'])
	print("���� 00�� ���� : ", info['closing_price'])
	print("���� 00�� ���� : ", info['min_price'])
	print("�� 00�� ���� : ", info['max_price'])
	print("�ŷ��� 00�� ���� : ", info['units_traded'])
	print("�ŷ��ݾ� 00�� ���� : ", info['prev_closing_price'])
	print("�������� : ", info['acc_trade_value'])
	print("�ֱ� 24�ð� �ŷ��� : ", info['units_traded_24H'])
	print("�ֱ� 24�ð� �ŷ��ݾ� : ", info['acc_trade_value_24H'])
	print("�ֱ� 24�ð� ������ : ", info['fluctate_24H'])
	print("�ֱ� 24�ð� ������ : ", info['fluctate_rate_24H'])
	*/

/* ����� */
/*void CoinAPI::StockSymbol()
{
	PyObject* pName, * pModule, * pFunc, * pValue, * objectsRepresentation;

	Py_Initialize();

	pName = PyUnicode_FromString("SpaceCoin_CoinAPI"); // xxx.py�� PyObject�� ����
	pModule = PyImport_Import(pName); // ������ PyObject pName�� import
	pFunc = PyObject_GetAttrString(pModule, "requestStockSymbols"); // ������ �Լ��� PyObject�� ���� 
	pValue = PyObject_CallObject(pFunc, NULL); // pFunc�� �Ű������� �����ؼ� ����. ���� �Ű������� NULL�� ���

	int count = 201;
	vector<string> stock_symbols(count);  // �迭 ������ vector ����
	const char* return_val;

	for (int i = 0; i < count; ++i) {
		int low = i;
		int high = i + 1;
		PyObject* p = PyList_GetSlice(pValue, low, high);
		objectsRepresentation = PyObject_Repr(p); // ��ü�� ���ڿ��� ǥ��
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // ��ü�� ���ڵ�
		return_val = PyBytes_AsString(str); // string���� ��ȯ�Ͽ� ��
		stock_symbols[i] = return_val;
		cout << stock_symbols[i] << endl;
	}
}*/

/* ���� ���� */
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

	pName = PyUnicode_FromString("SpaceCoin_CoinAPI"); // xxx.py�� PyObject�� ����
	pModule = PyImport_Import(pName); // ������ PyObject pName�� import
	pFunc = PyObject_GetAttrString(pModule, "requestInfo"); // ������ �Լ��� PyObject�� ���� 
	PyObject* pArgs = PyTuple_New(2);
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", c_stock_symbol));
	PyTuple_SetItem(pArgs, 1, Py_BuildValue("s", c_field));
	pValue = PyObject_CallObject(pFunc, pArgs); // pFunc�� �Ű������� �����ؼ� ����

	objectsRepresentation = PyObject_Repr(pValue); // ��ü�� ���ڿ��� ǥ��
	PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // ��ü�� ���ڵ�
	string result = PyBytes_AsString(str); // string���� ��ȯ�Ͽ� ��
	cout << result;

	/*
	print("�ð� 00�� ���� : ", info['opening_price'])
	print("���� 00�� ���� : ", info['closing_price'])
	print("���� 00�� ���� : ", info['min_price'])
	print("�� 00�� ���� : ", info['max_price'])
	print("�ŷ��� 00�� ���� : ", info['units_traded'])
	print("�ŷ��ݾ� 00�� ���� : ", info['prev_closing_price'])
	print("�������� : ", info['acc_trade_value'])
	print("�ֱ� 24�ð� �ŷ��� : ", info['units_traded_24H'])
	print("�ֱ� 24�ð� �ŷ��ݾ� : ", info['acc_trade_value_24H'])
	print("�ֱ� 24�ð� ������ : ", info['fluctate_24H'])
	print("�ֱ� 24�ð� ������ : ", info['fluctate_rate_24H'])
	*/

	//Py_Finalize();
//}


/* �Ű������� return ���� ���� �Լ� */
/*pName = PyUnicode_FromString("SpaceCoin_CoinAPI"); // xxx.py�� PyObject�� ����
pModule = PyImport_Import(pName); // ������ PyObject pName�� import
pFunc = PyObject_GetAttrString(pModule, "requestTicker"); // ������ �Լ��� PyObject�� ����
pValue = PyObject_CallObject(pFunc, NULL); // pFunc�� �Ű������� �����ؼ� ����. ���� �Ű������� NULL�� ���*/

/* ���ڿ� �Ű������� string�� return ���� �ִ� �Լ� */
/*pName = PyUnicode_FromString("SpaceCoin_CoinAPI"); // xxx.py�� PyObject�� ����
pModule = PyImport_Import(pName); // ������ PyObject pName�� import
pFunc = PyObject_GetAttrString(pModule, "test_func"); // ������ �Լ��� PyObject�� ����
pArg = Py_BuildValue("(z)", (const char*)"hello"); // ���ڿ� hello�� ���� �Ű������� ����
pValue = PyObject_CallObject(pFunc, pArg); // pFunc�� �Ű������� �����ؼ� ����

PyObject* objectsRepresentation = PyObject_Repr(pValue); // ��ü�� ���ڿ��� ǥ��
PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // ��ü�� ���ڵ�
string result = PyBytes_AsString(str); // string���� ��ȯ�Ͽ� ��
cout << result;*/

/* int�� �Ű������� int�� �迭 return ���� �ִ� �Լ� */
/*pName = PyUnicode_FromString("SpaceCoin_CoinAPI"); // xxx.py�� PyObject�� ����
pModule = PyImport_Import(pName); // ������ PyObject pName�� import
pFunc = PyObject_GetAttrString(pModule, "test_func"); // ������ �Լ��� PyObject�� ����
pArg = Py_BuildValue("(i, i, i, i)", 1, 2, 3, 4); // int�� ���� 4���� ����
pValue = PyObject_CallObject(pFunc, pArg); // pFunc�� �Ű������� �����ؼ� ����

int count = (int)PyList_Size(pValue); // count ������ �Լ����� ��ȯ�� �迭�� size�� ����
vector<int> arr(count); // �迭�� ������ vector ����
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