#include <iostream>
#include <fstream>
#include "CSVReader.h"

CSVReader::CSVReader()
{
}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename)
{
    std::vector<OrderBookEntry> entries;
    std::fstream csvFile{csvFilename};
    std::string line;
    if (csvFile.is_open())
    {
        while (std::getline(csvFile, line))
        {
            try
            {
                OrderBookEntry obe = stringsToOBE(tokenize(line, ','));
                entries.push_back(obe);
            }
            catch (const std::exception &e)
            {
            }
        }
        std::cout << "CSVReader::readCSV read: " << entries.size() << " entries" << std::endl;
    }
    return entries;
}

OrderBookEntry CSVReader::stringsToOBE(std::string timestamp,
                                       std::string product,
                                       OrderBookType orderType,
                                       std::string priceString,
                                       std::string amountString)
{
    double price, amount;
    try
    {
        price = std::stod(priceString);
        amount = std::stod(amountString);
    }
    catch (const std::exception &e)
    {
        std::cerr << "CSVReader::stringsToOBE | Bad Float format in input data: " << e.what() << std::endl;
    }
    OrderBookEntry obe{timestamp, product, orderType, price, amount};
    return obe;
}

std::vector<std::string> CSVReader::tokenize(std::string csvLine, char separator)
{
    std::vector<std::string> tokens;
    size_t start, end = 0;
    // simplified this code because it was confusing to me
    // starts by creating a loop so long as the seperator can still be found
    while ((start = csvLine.find_first_not_of(separator, end)) != std::string::npos)
    {
        // finds the next seperator and change the end index
        end = csvLine.find(separator, start);
        // add the elements found to the vector
        tokens.push_back(csvLine.substr(start, end - start));
    }

    return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
    if (tokens.size() != 5)
    { // Ensuring correct number of tokens
        std::cerr << "CSVReader::stringsToOBE | Bad Line: Incorrect number of elements" << std::endl;
        throw std::runtime_error("Bad Line: Incorrect format");
    }

    double price = 0.0;
    double amount = 0.0;

    try
    {
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }
    catch (const std::exception &e)
    {
        std::cerr << "CSVReader::stringsToOBE | Bad Float format in input data: " << e.what() << std::endl;
        throw;
    }

    OrderBookEntry obe{tokens[0], tokens[1], OrderBookEntry::stringToOrderBookType(tokens[2]), price, amount};
    return obe;
}