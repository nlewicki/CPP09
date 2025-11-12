/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:04:11 by nlewicki          #+#    #+#             */
/*   Updated: 2025/11/12 09:03:10 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <chrono>

int main(int argc, char* argv[])
{
    PmergeMe sorter;
    try
    {
        sorter.parseInput(argc, argv);
        DDisplay("Vector before sorting: ", sorter.getVector());
        DDisplay("Deque before sorting: ", sorter.getDeque());
        sorter.exec();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}