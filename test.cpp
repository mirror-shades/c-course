#include <string>
#include <vector>
#include <iostream>
#include <fstream>

std::vector<std::string> tokenize(std::string csvLine, char separator)
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

void calculateValueToday(std::vector<double> cpiData)
{
    double price = 1;
    for (double &c : cpiData)
    {
        price = price * (1 + c / 100);
    }
    std::cout << "Value of $1 from 1960 in 2022: $" << price << std::endl;
    std::cout << "A 5.00 fast food meal would have been " << 5 / price << std::endl;
    std::cout << "A 25,000 dollar car would have been " << 25000 / price << std::endl;
    std::cout << "A 500,000 dollar house would have been " << 500000 / price << std::endl;
}

std::vector<double> readCPIData(std::vector<std::string> tokens)
{
    std::vector<double> cpiData;
    int nonce = 0;
    int year = 1960;
    for (std::string &t : tokens)
    {
        if (nonce >= 5)
        {
            std::cout << year << ": " << t << std::endl;
            cpiData.push_back(std::stod(t));
            year++;
        }
        nonce++;
    }
    return cpiData;
}

int main()
{
    std::ifstream csvFile{"cpi.csv"};
    std::string line;
    std::vector<std::string> tokens;
    std::vector<double> cpiData;
    if (csvFile.is_open())
    {
        std::cout << "CSV file opened successfully" << std::endl;
        while (std::getline(csvFile, line))
        {
            tokens = tokenize(line, ',');
            if (tokens[0] == "United States")
            {
                cpiData = readCPIData(tokens);
                std::cout << "==============" << std::endl;
                calculateValueToday(cpiData);
            }
        }
        csvFile.close();
    }

    return 0;
}