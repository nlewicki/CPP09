/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:35:29 by nlewicki          #+#    #+#             */
/*   Updated: 2025/11/04 13:19:38 by nlewicki         ###   ########.fr       */
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

void BitcoinExchange::processInputFile(const std::string& filename) const
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Could not open input file." << std::endl;
        return;
    }

    std::string line;
    while (checkInput(const std::getline(file, line)))
    {
        // Process each line
    }
}