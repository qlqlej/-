import requests
from requests.exceptions import HTTPError
import json
from urllib import request, parse
import ssl
import certifi
import time

api_url = "https://api.bithumb.com/public/ticker/ALL_KRW"
api_key = "af2e3893087d05f9a33bcaddc1db5cdb";  # connect key
api_secret = "e6cf199abe2b47e9bffecbf478690818";  # secret key

def __init__(self, api_key, api_secret):
    self.api_key = api_key;
    self.api_secret = api_secret;

def requestStockSymbols():  # 종목명
    api_url = "https://api.bithumb.com/public/ticker/ALL_KRW"
    req = request.Request(api_url)
    res = request.urlopen(req)
    resultString = res.read().decode('utf-8')
    # print(resultString)  # 읽어오기

    json_object = json.loads(resultString)  # json 데이터 load

    # print("status : " + json_object['status'])

    data = json_object['data']
    del(data['date'])  # 마지막 date 삭제
    
    stock_symbols = []
    for key in data:
        stock_symbols.append(key)

    return stock_symbols

def requestStockSymbolsLen():  # 종목수
    count = len(requestStockSymbols())
    return count

def requestInfo(stock_symbol, field):
    api_url = "https://api.bithumb.com/public/ticker/ALL_KRW"
    req = request.Request(api_url)
    res = request.urlopen(req)
    resultString = res.read().decode('utf-8')
    # print(resultString)  # 읽어오기

    json_object = json.loads(resultString)  # json 데이터 load

    # print("status : " + json_object['status'])

    data = json_object['data']
    del(data['date'])  # 마지막 date 삭제
    info = data[stock_symbol]  # 종목별 정보

    return info[field]

    '''
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
    print("-------------------------------------------------------")
    '''
        
def requestTicker():
    api_url = "https://api.bithumb.com/public/ticker/ALL_KRW"
    req = request.Request(api_url)
    res = request.urlopen(req)
    resultString = res.read().decode('utf-8')
    # print(resultString)  # 읽어오기

    json_object = json.loads(resultString)  # json 데이터 load

    print("status : " + json_object['status'])

    data = json_object['data']
    del(data['date'])  # 마지막 date 삭제

    stock_symbols = data.keys  # 종목명

    return data
    '''
    print("종목명 : BTC")
    info = data['BTC']
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
    print("-------------------------------------------------------")
    '''
    '''
    for key in data:  # 종목별 정보
        print("종목명 : ", key)
        info = data[key]
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
        print("-------------------------------------------------------")
        
        #return key
    '''

def requestOrderbook():
   api_url = "https://api.bithumb.com/public/orderbook/ALL_KRW"
   req = request.Request(api_url)
   res = request.urlopen(req)
   resultString = res.read().decode('utf-8')
   # print(resultString)  # 읽어오기

   json_object = json.loads(resultString)  # json 데이터 load

   print("status : " + json_object['status'])

   data = json_object['data']

   print(data)
   '''
   print("타임 스탬프 : ", data['timestamp'])
   print("결제 통화 (마켓) : ", data['payment_currency'])

   print("주문 통화 (코인) : ", data['order_currency'])
   print("매수 요청 내역 : ", data['bids'])
   print("매도 요청 내역 : ", data['asks'])
   print("Currency 수량 : ", data['quantity'])
   print("Currency 거래가 : ", data['price'])
   print("-------------------------------------------------------")
   '''
