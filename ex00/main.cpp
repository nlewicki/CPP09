/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:35:35 by nlewicki          #+#    #+#             */
/*   Updated: 2025/11/05 09:10:01 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char** argv)
{
    if (argc != 2 || (std::string(argv[1]) != "input.txt"))
    {
        std::cerr << "Usage: " << argv[0] << " <input.txt>" << std::endl;
        return 1;
    }

    BitcoinExchange bitcoinExchange;

    bitcoinExchange.loadData("data.csv");
    // bitcoinExchange.printData();
    bitcoinExchange.processInputFile(argv[1]);

    return 0;
}