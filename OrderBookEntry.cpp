#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(std::string _timestamp, std::string _product, OrderBookType _orderType, double _price, double _amount)
    : timestamp(_timestamp), product(_product), orderType(_orderType), price(_price), amount(_amount) {}

bool OrderBookEntry::compareByTimestamp(OrderBookEntry e1, OrderBookEntry e2)
{
    return e1.timestamp < e2.timestamp;
}

bool OrderBookEntry::compareByPriceAsc(OrderBookEntry e1, OrderBookEntry e2)
{
    return e1.price < e2.price;
}

bool OrderBookEntry::compareByPriceDesc(OrderBookEntry e1, OrderBookEntry e2)
{
    return e1.price > e2.price;
}

OrderBookType OrderBookEntry::stringToOrderBookType(std::string s)
{
    if (s == "ask")
    {
        return OrderBookType::ask;
    }
    if (s == "bid")
    {
        return OrderBookType::bid;
    }
    return OrderBookType::unknown;
}