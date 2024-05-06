#include "Wallet.h"
#include "CSVReader.h"


Wallet::Wallet()
{
}

void Wallet::insertCurrency(std::string type, double amount)
{
    double balance;
    if(amount < 0)
    {
        throw std::exception{};
    }
    if(currencies.count(type) == 0)
    {
        balance = 0;
    } else {
        balance = currencies[type];
    }
    balance += amount;
    currencies[type] = balance;
}

bool Wallet::removeCurrency(std::string type, double amount)
{
    double balance;
    if(amount < 0)
    {
        return false;
    }
    if(currencies.count(type) == 0)
    {
        return false;
    } else {
        if(containsCurrency(type, amount)){
            currencies[type] -= amount;
            return true;
        }
    
    else return false;
    }
}

bool Wallet::containsCurrency(std::string type, double amount)
{
    double balance;
    if(currencies.count(type) == 0)
    {
        return false;
    } else {
        return currencies[type] >= amount;
    }
}

std::string Wallet::toString()
{
    std::string s;
    for(std::pair<std::string, double> pair : currencies)
    {
        std::string currency = pair.first;
        double amount = pair.second;
        s += currency + " : " + std::to_string(amount) + "\n";
    }
    return s;
}

bool Wallet::canFufillOrder(OrderBookEntry order)
{
    std::vector<std::string> currs = CSVReader::tokenize(order.product, '/');
    if(order.orderType == OrderBookType::ask)
    {
        double amount = order.amount;
        std::string currency = currs[0];
        return containsCurrency(currency, amount);
    }
    if(order.orderType == OrderBookType::ask)
    {
        double amount = order.amount * order.price;
        std::string currency = currs[1];
        return containsCurrency(currency, amount);
    }
    return false;
}