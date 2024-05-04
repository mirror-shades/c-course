#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
public:
    /** construct, reading a csv data file, return vector of product and of filter*/
    OrderBook(std::string filename);
    std::vector<std::string> getKnownProducts();
    std::vector<OrderBookEntry> getOrders(OrderBookType type,
                                          std::string product,
                                          std::string timestamp);
    std::string getEarliestTime();
    std::string getNextTime(std::string timestamp);

    void insertOrder(OrderBookEntry &order);

    std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

    static double getCurrentVolume(std::vector<OrderBookEntry> &orders, std::string timestamp);
    static double getLowPrice(std::vector<OrderBookEntry> &orders);
    static double getHighPrice(std::vector<OrderBookEntry> &orders);

private:
    std::vector<OrderBookEntry> orders;
};