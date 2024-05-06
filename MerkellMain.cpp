#include "MerkellMain.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "Wallet.h"
#include <iostream>
#include <limits>
#include <vector>

MerkellMain::MerkellMain()
{
}

int MerkellMain::init()
{
    currentTime = orderBook.getEarliestTime();
    // wallet.insertCurrency("BTC", 10);
    while (true)
    {
        showOptions();
        int option = getSelection();
        handleSelection(option);
        if (option == 7)
        {
            return 0;
        }
    }
}

void MerkellMain::showOptions()
{
    std::cout << std::endl
              << "1: Print help " << std::endl
              << "2: Print exchange stats " << std::endl
              << "3: Make an ask " << std::endl
              << "4: Make a bid " << std::endl
              << "5: Print wallet " << std::endl
              << "6: Continue " << std::endl
              << "7: Exit " << std::endl
              << "==============" << std::endl
              << "Enter 1-7 " << std::endl
              << "Current time is " << currentTime << std::endl;
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
    std::cout << "Here are the market stats" << std::endl;
    listEntries();
}

void MerkellMain::makeAsk()
{
    std::cout << "Make an ask - enter [product, price, amount]" << std::endl;
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenize(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "bad input: " << input << std::endl;
    }
    else
    {
        OrderBookEntry obe = CSVReader::stringsToOBE(currentTime,
                                                     tokens[0],
                                                     OrderBookType::ask,
                                                     tokens[1],
                                                     tokens[2]);
        if (wallet.canFufillOrder(obe))
        {
            orderBook.insertOrder(obe);
        }
        else
        {
            std::cout << "insufficent funds" << std::endl;
        }
    }
    std::cout << input << std::endl;
}

void MerkellMain::makeBid()
{
    std::cout << "Make an bid - enter [product, price, amount]" << std::endl;
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenize(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "bad input: " << input << std::endl;
    }
    else
    {
        OrderBookEntry obe = CSVReader::stringsToOBE(currentTime,
                                                     tokens[0],
                                                     OrderBookType::bid,
                                                     tokens[1],
                                                     tokens[2]);
        if (wallet.canFufillOrder(obe))
        {
            orderBook.insertOrder(obe);
        }
        else
        {
            std::cout << "insufficent funds" << std::endl;
        }
    }
    std::cout << input << std::endl;
}

void MerkellMain::showWallet()
{
    std::cout << wallet.toString() << std::endl;
}

void MerkellMain::nextTimeFrame()
{
    std::cout << "Okay, onto the next time frame" << std::endl;
    std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids("ETH/BTC", currentTime);
    for (OrderBookEntry sale : sales)
    {
        std::cout << "Sale Made pf ETH/BTC @ " << sale.price << ", " << sale.amount << std::endl;
    }
    currentTime = orderBook.getNextTime(currentTime);
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
        makeAsk();
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

// void MerkellMain::computeAveragePrice()
// {
//     double sum = 0;
//     for (auto &entry : orders)
//     {
//         sum += entry.price;
//     }
//     std::cout << "Average price: " << sum / orders.size() << std::endl;
// }

void MerkellMain::listEntries()
{
    for (std::string const &p : orderBook.getKnownProducts())
    {
        std::vector<OrderBookEntry> entriesA = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        std::vector<OrderBookEntry> entriesB = orderBook.getOrders(OrderBookType::bid, p, currentTime);
        double aV = OrderBook::getCurrentVolume(entriesA, currentTime);
        double bV = OrderBook::getCurrentVolume(entriesB, currentTime);
        std::cout
            << "Product: " << p << std::endl;
        std::cout << "Asks seen: " << entriesA.size() << std::endl;
        std::cout << "Bids seen: " << entriesB.size() << std::endl;
        std::cout << "Current Ask: " << OrderBook::getHighPrice(entriesA) << std::endl;
        std::cout << "Product volume | Asks: " << aV << " Bids: " << bV << std::endl;
    }
}