#include "MerkellMain.h"
#include "OrderBookEntry.h"
#include <iostream>
#include <limits>
#include <vector>

std::vector<OrderBookEntry> entries;

MerkellMain::MerkellMain()
{
}

int MerkellMain::init()
{
    while (true)
    {
        makeTestBook();
        showOptions();
        int option = getSelection();
        handleSelection(option);
        if (option == 7)
        {
            return 0;
        }
    }
}

void MerkellMain::makeTestBook()
{
    OrderBookEntry obe1("2020/03/17 17:02:30.884493", "ETH/BTC", OrderBookType::ask, 0.02314308, 0.44564869);
    OrderBookEntry obe2("2020/03/17 17:02:30.884493", "ETH/BTC", OrderBookType::ask, 0.02284637, 0.15);
    OrderBookEntry obe3("2020/03/17 17:02:30.884493", "ETH/BTC", OrderBookType::ask, 0.02248988, 2.665);
    OrderBookEntry obe4("2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::bid, 0.02126299, 0.1);
    OrderBookEntry obe5("2020/03/17 17:02:30.884493", "ETH/BTC", OrderBookType::bid, 0.02105731, 1.75);
    OrderBookEntry obe6("2020/03/17 17:02:30.884493", "ETH/BTC", OrderBookType::bid, 0.02079121, 0.0225);
    entries.push_back(obe1);
    entries.push_back(obe2);
    entries.push_back(obe3);
    entries.push_back(obe4);
    entries.push_back(obe5);
    entries.push_back(obe6);
}
void MerkellMain::showOptions()
{
    std::cout << std::endl
              << "1: Print help " << std::endl
              << "2: Print exchange stats " << std::endl
              << "3: Make an offer " << std::endl
              << "4: Make a bid " << std::endl
              << "5: Print wallet " << std::endl
              << "6: Continue " << std::endl
              << "7: Exit " << std::endl
              << "==============" << std::endl
              << "Enter 1-7 " << std::endl;
}
void MerkellMain::invalidEntry()
{
    std::cout << "Invalid entry" << std::endl;
    std::cout << "Enter 1-7 " << std::endl;
}

void MerkellMain::showHelp()
{
    std::cout << "Help - Your aim is to make money. Go get 'em champ!" << std::endl;
}

void MerkellMain::showMarketStats()
{
    /**this is where the test are conducted, to simulate checking market data*/
    listEntries();
    computePriceSpread();
    computeAveragePrice();
}

void MerkellMain::makeOffer()
{
    std::cout << "You made an offer" << std::endl;
}

void MerkellMain::makeBid()
{
    std::cout << "You made a bid" << std::endl;
}

void MerkellMain::showWallet()
{
    std::cout << "You are broke" << std::endl;
}

void MerkellMain::nextTimeFrame()
{
    std::cout << "Okay, onto the next time frame" << std::endl;
}

void MerkellMain::goodbye()
{
    std::cout << "Goodbye!" << std::endl;
}

void MerkellMain::handleSelection(int option)
{
    std::cout << "You chose " << option << std::endl;

    if (option == 0)
    {
        invalidEntry();
    }
    if (option == 1)
    {
        showHelp();
    }
    if (option == 2)
    {
        showMarketStats();
    }
    if (option == 3)
    {
        makeOffer();
    }
    if (option == 4)
    {
        makeBid();
    }
    if (option == 5)
    {
        showWallet();
    }
    if (option == 6)
    {
        nextTimeFrame();
    }
    if (option == 7)
    {
        goodbye();
    }
}

int MerkellMain::getSelection()
{
    int option;
    std::cin >> option;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        option = 0;
    }
    return option;
}

void MerkellMain::computeAveragePrice()
{
    double sum = 0;
    for (auto &entry : entries)
    {
        sum += entry.price;
    }
    std::cout << "Average price: " << sum / entries.size() << std::endl;
}
double MerkellMain::computeLowPrice()
{
    double low = 0;
    for (auto &entry : entries)
    {
        /**to find the lowest price we take the highest bid*/
        if (entry.price > low && entry.orderType == OrderBookType::bid)
        {
            low = entry.price;
        }
    }
    std::cout << "Low price: " << low << std::endl;
    return (low);
}
double MerkellMain::computeHighPrice()
{
    double high = std::numeric_limits<double>::max(); // starts at the max value for search purposes
    for (auto &entry : entries)
    {
        /**to find the highest price we take the lowest ask*/
        if (entry.price < high && entry.orderType == OrderBookType::ask)
        {
            high = entry.price;
        }
    }
    std::cout << "High price: " << high << std::endl;
    return (high);
}
void MerkellMain::computePriceSpread()
{
    double high = computeHighPrice();
    double low = computeLowPrice();
    double spread = high - low;
    std::cout << "Spread in price: " << spread << std::endl;
}

void MerkellMain::listEntries()
{
    for (auto &entry : entries)
    {
        std::cout << entry.timestamp << ", "
                  << entry.product << ", "
                  << (entry.orderType == OrderBookType::bid ? "bid" : "ask") << ", "
                  << entry.price << ", "
                  << entry.amount << std::endl;
    }
}