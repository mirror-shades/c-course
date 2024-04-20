#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(std::string _timestamp, std::string _product, OrderBookType _orderType, double _price, double _amount)
    : timestamp(_timestamp), product(_product), orderType(_orderType), price(_price), amount(_amount) {}
