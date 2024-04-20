#pragma once

#include <string>

enum class OrderBookType
{
    bid,
    ask
};
class OrderBookEntry
{
public:
    /** Create a new OrderBookEntry with the price
     * set to the sent value
     */
    OrderBookEntry(std::string _timestamp, std::string _product, OrderBookType _orderType, double _price, double _amount);
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
    double price;
    double amount;
};