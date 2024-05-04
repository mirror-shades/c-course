#include "OrderBook.h"
#include "CSVReader.h"
#include <limits>
#include <algorithm>
#include <map>
#include <iostream>

OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
}

std::string OrderBook::getEarliestTime()
{
    return orders[0].timestamp;
}

double OrderBook::getCurrentVolume(std::vector<OrderBookEntry> &orders, std::string timestamp)
{
    double res = 0;
    for (OrderBookEntry &e : orders)
    {
        if (e.timestamp <= timestamp)
        {
            res = +e.amount;
        }
    }
    return res;
}

std::string OrderBook::getNextTime(std::string timestamp)
{
    std::string nextTimestamp = "";
    for (OrderBookEntry &e : orders)
    {
        if (e.timestamp > timestamp)
        {
            nextTimestamp = e.timestamp;
            break;
        }
        if (nextTimestamp == "")
        {
            nextTimestamp = orders[0].timestamp;
        }
    }
    return nextTimestamp;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry> &orders)
{
    double high = std::numeric_limits<double>::max(); // starts at the max value for search purposes
    for (OrderBookEntry &entry : orders)
    {
        std::string _type = "no type";
        if (entry.orderType == OrderBookType::ask)
        {
            _type = "ask";
        }
        if (entry.orderType == OrderBookType::bid)
        {
            _type = "bid";
        }
        /**to find the highest price we take the lowest ask*/
        if (entry.price < high && entry.orderType == OrderBookType::ask)
        {
            high = entry.price;
        }
    }
    return (high);
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry> &orders)
{
    double min = 0; // starts at the max value for search purposes
    for (OrderBookEntry &entry : orders)
    {
        std::string _type = "no type";
        if (entry.orderType == OrderBookType::ask)
        {
            _type = "ask";
        }
        if (entry.orderType == OrderBookType::bid)
        {
            _type = "bid";
        }
        /**to find the highest price we take the lowest ask*/
        if (entry.price > min && entry.orderType == OrderBookType::ask)
        {
            min = entry.price;
        }
    }
    return (min);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);

    std::vector<OrderBookEntry> sales;

    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);

    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

    for (OrderBookEntry &ask : asks)
    {
        for (OrderBookEntry &bid : bids)
        {
            if (bid.price >= ask.price)
            {
                OrderBookEntry sale{timestamp, product, OrderBookType::sale, ask.price, 0};
                if (bid.amount == ask.amount)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;
                    break;
                }
                if (bid.amount > ask.amount)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = bid.amount - ask.amount;
                    break;
                }
                if (bid.amount < ask.amount)
                {
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    bid.amount = ask.amount - bid.amount;
                    continue;
                }
            }
        }
    }
    return sales;
}

void OrderBook::insertOrder(OrderBookEntry &order)
{
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;

    std::map<std::string, bool> prodMap;

    for (OrderBookEntry &e : orders)
    {
        prodMap[e.product] = true;
    }

    for (auto const &e : prodMap)
    {
        products.push_back(e.first);
    }

    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                                 std::string product,
                                                 std::string timestamp)
{
    std::vector<OrderBookEntry> _orders;
    for (OrderBookEntry &e : orders)
    {
        if (e.orderType == type &&
            e.product == product &&
            e.timestamp == timestamp)
        {
            _orders.push_back(e);
        }
    }
    return _orders;
}