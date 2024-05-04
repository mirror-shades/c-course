#pragma once

#include "OrderBookEntry.h"
#include <vector>

class CSVReader
{
public:
    CSVReader();
    static std::vector<OrderBookEntry> readCSV(std::string csvFile);
    static std::vector<std::string> tokenize(std::string csvLine, char separator);
    static OrderBookEntry stringsToOBE(std::string timestamp,
                                       std::string product,
                                       OrderBookType orderType,
                                       std::string price,
                                       std::string amount);

private:
    static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
};