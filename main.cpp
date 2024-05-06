#include "MerkellMain.h"
#include "Wallet.h"
#include <iostream>

int main()
{
    // MerkellMain app{};
    // app.init();
    Wallet wallet;
    wallet.insertCurrency("BTC", 10);

    // should return true:
    // exact amount
    bool test1 = wallet.containsCurrency("BTC", 10);
    // lower amount
    bool test2 = wallet.containsCurrency("BTC", 5);

    // should return false:
    // wrong currency
    bool test3 = wallet.containsCurrency("ETH", 10);
    // amount too high
    bool test4 = wallet.containsCurrency("BTC", 15);

    if (test1 == true && test2 == true && test3 == false && test4 == false)
    {
        std::cout << "Tests Passed!" << std::endl;
    }
    else
    {
        std::cout << "Tests have failed!" << std::endl;
    }
}
