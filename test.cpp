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

int main()
{
    std::ifstream csvFile{"cpi.csv"};
    std::string line;
    std::vector<std::string> tokens;
    if (csvFile.is_open())
    {
        std::cout << "CSV file opened successfully" << std::endl;
        while (std::getline(csvFile, line))
        {
            tokens = tokenize(line, ',');
            if (tokens[0] == "United States")
            {
                std::cout << "us found" << std::endl;
                for (std::string &t : tokens)
                {
                    std::cout << t << " ";
                }
            }
        }
        csvFile.close();
    }

    return 0;
}