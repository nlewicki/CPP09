/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:04:30 by nlewicki          #+#    #+#             */
/*   Updated: 2025/11/14 08:59:34 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
    
}

PmergeMe::~PmergeMe()
{
    
}

void DDisplay_txt(const std::string& message)
{
    #ifdef DEBUG
    std::cout << message << std::endl;
    #endif
    (void)message;
}

template <typename T>
void check_sorted(const T& c, const char* name)
{
    #ifdef DEBUG
    for (typename T::size_type i = 1; i < c.size(); ++i)
    {
        if (c[i - 1] > c[i])
        {
            std::cerr << name << " NOT sorted at index "
                      << (i - 1) << " -> " << i
                      << " (" << c[i - 1] << " > " << c[i] << ")\n";
            return;
        }
    }
    std::cout << name << " sorted ✅\n";
    #endif
    (void)c;
    (void)name;
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
            // Check if token is a valid number
            if (!isValidNumber(token))
                throw std::runtime_error("Error: Invalid number '" + token + "'.");  

            char* end = 0;
            long num = std::strtol(token.c_str(), &end, 10);
            // Check for conversion errors
            if (*end != '\0')  
                throw std::runtime_error("Error: Invalid number '" + token + "'.");
            // Check for range of int
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

void PmergeMe::exec()
{
    DDisplay("Vector before sorting: ", _vector);
    DDisplay("Deque before sorting: ", _deque);
    
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    sort_vector();
    check_sorted(_vector, "vector");
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> duration_vec = end - start;

    start = std::chrono::high_resolution_clock::now();
    sort_deque();
    check_sorted(_deque,  "deque");
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> duration_deq = end - start;
    
    Display("After: ", _vector);
    std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector : " << std::fixed << duration_vec.count() << " µs" << std::endl;
    std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque  : " << std::fixed << duration_deq.count() << " µs" << std::endl;
}

