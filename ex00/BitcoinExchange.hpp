/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:35:33 by nlewicki          #+#    #+#             */
/*   Updated: 2025/11/04 13:26:46 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <stdexcept>
#include <ctime>

class BitcoinExchange
{
    private:
        std::map<std::string, float> _data;
        
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& source);
        BitcoinExchange& operator=(const BitcoinExchange& source);
        ~BitcoinExchange();
        

        void loadData(const std::string& filename); // load csv data into _data map
        void printData() const; // for debugging purposes
        bool checkInput(const std::string& line) const; // loop(checkInput) -> if true, get rate -> if false, error msg(which is in checkInput) and dont go in get rate. next line
        float getExchangeRate(const std::string& date) const; // get rate from _data map -> if date not found, find closest previous date
        void processInputFile(const std::string& filename) const; // process input file line by line

};

#endif