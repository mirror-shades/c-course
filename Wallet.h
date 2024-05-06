#pragma once
#include "OrderBookEntry.h"
#include <string>
#include <map>

class Wallet
{
public:
    Wallet();
    void insertCurrency(std::string type, double amount);
    bool removeCurrency(std::string type, double amount);
    bool containsCurrency(std::string type, double amount);
    bool canFufillOrder(OrderBookEntry order);
    std::string toString();


private:
    std::map<std::string, double> currencies;
};