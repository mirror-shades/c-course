#pragma once
#include "OrderBook.h"
#include "Wallet.h"

class MerkellMain
{
public:
    MerkellMain();
    /** call this to start the sim */
    int init();

private:
    void showOptions();
    void invalidEntry();
    void showHelp();
    void showMarketStats();
    void makeAsk();
    void makeBid();
    void showWallet();
    void nextTimeFrame();
    void goodbye();
    void handleSelection(int option);
    int getSelection();
    void computeAveragePrice();
    double computeLowPrice();
    double computeHighPrice();
    void computePriceSpread();
    void listEntries();

    OrderBook orderBook{"marketData.csv"};
    std::string currentTime;
    Wallet wallet;
};