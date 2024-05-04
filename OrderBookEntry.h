#pragma once

#include <string>

enum class OrderBookType
{
    bid,
    ask,
    sale,
    unknown
};
class OrderBookEntry
{
public:
    /** Create a new OrderBookEntry with the price
     * set to the sent value
     */
    OrderBookEntry(std::string _timestamp, std::string _product, OrderBookType _orderType, double _price, double _amount);

    static OrderBookType stringToOrderBookType(std::string s);

    static bool compareByTimestamp(OrderBookEntry e1, OrderBookEntry e2);
    static bool compareByPriceAsc(OrderBookEntry e1, OrderBookEntry e2);
    static bool compareByPriceDesc(OrderBookEntry e1, OrderBookEntry e2);

    std::string timestamp;
    std::string product;
    OrderBookType orderType;
    double price;
    double amount;
};