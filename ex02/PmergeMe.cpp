/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:04:30 by nlewicki          #+#    #+#             */
/*   Updated: 2025/11/12 09:04:02 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
    
}

PmergeMe::~PmergeMe()
{
    
}

bool PmergeMe::isValidNumber(const std::string& str) const
{
    if (str.empty())
        return false;

    size_t i = 0;
    if (str[0] == '+')
    {
        if (str.size() == 1)
            return false;
        i = 1;
    }

    for (; i < str.size(); i++)
    {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

void PmergeMe::parseInput(int argc, char* argv[])
{
    if (argc < 2)
        throw std::runtime_error("Error: Not enough arguments.");
    
    for (int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);
        std::istringstream iss(arg);
        std::string token;

        while (iss >> token)
        {
            if (!isValidNumber(token))
                throw std::runtime_error("Error: Invalid number '" + token + "'.");  

            char* end = 0;
            long num = std::strtol(token.c_str(), &end, 10);
            
            if (*end != '\0')  
                throw std::runtime_error("Error: Invalid number '" + token + "'.");
                
            if (num < 0 || num > INT_MAX)  
                throw std::runtime_error("Error: Number out of range '" + token + "'.");
            
            int number = static_cast<int>(num);

            if (std::find(_vector.begin(), _vector.end(), number) != _vector.end())
                throw std::runtime_error("Error: Duplicate number '" + token + "'.");
            
            _vector.push_back(number);
            _deque.push_back(number);
            
        }
    }
    
    if (_vector.empty())
        throw std::runtime_error("Error: No valid numbers.");

    Display("Before: ", _vector);
}



std::vector<int> PmergeMe::getVector() const
{
    return _vector;
}

std::deque<int> PmergeMe::getDeque() const
{
    return _deque;
}

void PmergeMe::exec()
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    _vector = sort_vector(_vector);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> duration_vec = end - start;

    // start = std::chrono::high_resolution_clock::now();
    // std::sort(_deque.begin(), _deque.end());
    // end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double, std::micro> duration_deq = end - start;
    
    Display("After: ", _vector);
    std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector : " << std::fixed << duration_vec.count() << " µs" << std::endl;
    // std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque  : " << std::fixed << duration_deq.count() << " µs" << std::endl;
}

