/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:35:29 by nlewicki          #+#    #+#             */
/*   Updated: 2025/11/05 09:16:23 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& source)
{
    *this = source;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& source)
{
    if (this != &source)
    {
        this->_data = source._data;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{
    
}

static std::string trim(const std::string& s) {
    std::string::size_type a = s.find_first_not_of(" \t");
    std::string::size_type b = s.find_last_not_of(" \t");
    if (a == std::string::npos) return ""; // npos means string is all whitespace (= not found)
    return s.substr(a, b - a + 1);
}

void BitcoinExchange::loadData(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Could not open data file.");
    std::string line;
    
    // Skip header line
    std::getline(file, line);
    
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string date;
        float rate;
        if (std::getline(ss, date, ',') && (ss >> rate)) // read line -> date until comma, then rate
        {
            // std::cout << "lookup key1 = [" << date << "] (len=" << date.size() << ")\n";
            this->_data[date] = rate; // insert into map -> date as key, rate as value
        }
    }
}

void BitcoinExchange::printData() const
{
    for (std::map<std::string, float>::const_iterator it = this->_data.begin(); it != this->_data.end(); ++it)
    {
        std::cout << it->first << " => " << it->second << std::endl;
    }
}

void BitcoinExchange::printSolution(const std::string& line, float rate) const
{
    std::stringstream ss(line);
    std::string date;
    float value;

    if (std::getline(ss, date, '|') && (ss >> value))
    {
        date = trim(date);
        std::cout << date << " => " << value << " = " << value * rate << std::endl;
    }
}

void BitcoinExchange::processInputFile(const std::string& filename) const
{
    std::ifstream file(filename.c_str()); // open input file (c_str() to convert string to const char*)
    if (!file.is_open())
    {
        std::cerr << "Could not open input file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        if (!checkInput(line)) 
            continue;
        float rate = getExchangeRate(line); // get value from map
        printSolution(line, rate);
        // std::cout << "Processed line: " << line << " => " << rate  << std::endl;
    }
}


float BitcoinExchange::getExchangeRate(const std::string& line) const
{
    std::stringstream ss(line);
    std::string date;
    float value;

    // std::cout << "Processing line: " << line << std::endl;
    if (std::getline(ss, date, '|') && (ss >> value))
    {
        date = trim(date);
        // std::cout << "lookup key = [" << date << "] (len=" << date.size() << ")\n";
        std::map<std::string, float>::const_iterator it = this->_data.find(date);
        if (it != this->_data.end())
        {
            float rate = it->second;
            // std::cout << "Found exact date: ";
            // std::cout << date << " | " << value << " => value: " << value << " * rate: " << rate << std::endl;
            return rate;
        }
        else
        {
            // Find closest previous date
            it = this->_data.lower_bound(date); // first element not less than date
            if (it != this->_data.begin())
            {
                --it; // go to the closest previous date
                float rate = it->second;
                // std::cout << "Using closest previous date: ";
                // std::cout << it->first << " | " << value << " => value: " << value << " * rate: " << rate << std::endl;
                return rate;
            }
            else
            {
                std::cerr << "No exchange rate available for date: " << date << std::endl;
                return 0.0f;
            }
        }

    }
    return 0.0f;
}

bool BitcoinExchange::checkInput(const std::string& line) const
{
    std::stringstream ss(line);
    std::string date;
    float value;
    if (std::getline(ss, date, '|') && (ss >> value))
    {
        date = trim(date);
        // Validate date format
        if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        {
            std::cerr << "Error: bad date input => " << line << std::endl;
            return false;
        }
        int year = std::atoi(date.substr(0, 4).c_str());
        int month = std::atoi(date.substr(5, 2).c_str());
        int day = std::atoi(date.substr(8, 2).c_str());

        // validate month and day ranges
        if (month < 1 || month > 12 || day < 1 || day > 31)
        {
            std::cerr << "Error: bad month/day input => " << line << std::endl;
            return false;
        }

        // check for February
        if (month == 2 && day > 29)
        {
            std::cerr << "Error: bad day input for February => " << line << std::endl;
            return false;
        }
        
        // check for months with 30 days
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        {
                std::cerr << "Error: bad day input for month => " << line << std::endl;
                return false;
        }
        
        // check for limits of data.csv
        if (year < 2009 || year > 2022)
        {
            std::cerr << "Error: before/after limits of data.csv => " << line << std::endl;
            return false;
        }

        // mininmum date is 2009-01-02 and maximum is 2022-03-29

        if (date < "2009-01-02" || date > "2022-03-29")
        {
            std::cerr << "Error: date out of range => " << line << std::endl;
            return false;
        }

        // validate value range
        if (value < 0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            return false;
        }
        if (value > 1000)
        {
            std::cerr << "Error: too large a number." << std::endl;
            return false;
        }
    }
    else
    {
        std::cerr << "Error: bad input => " << line << std::endl;
        return false;
    }
    return true;
}