#pragma once

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
    void makeOffer();
    void makeBid();
    void showWallet();
    void nextTimeFrame();
    void goodbye();
    void handleSelection(int option);
    int getSelection();
    void makeTestBook();
    void computeAveragePrice();
    double computeLowPrice();
    double computeHighPrice();
    void computePriceSpread();
    void listEntries();
};