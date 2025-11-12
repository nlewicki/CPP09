#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <climits>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>


class PmergeMe
{
    private:
        std::vector<int> _vector;
        std::deque<int> _deque;
    
    public:
        PmergeMe();
        PmergeMe(const PmergeMe& source) = delete;
        PmergeMe& operator=(const PmergeMe& source) = delete;
        ~PmergeMe();

        void parseInput(int argc, char* argv[]);
        bool isValidNumber(const std::string& str) const;
        void exec();
        void sort_vector();
        void sort_deque();
};

void DDisplay_txt(const std::string& message);

template<typename T>
void Display(const std::string& message, T container)
{
    std::cout << message;
    typename T::iterator it = container.begin();
    while (it != container.end() - 1)
    {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << *it;
    std::cout << std::endl;
}

template<typename T>
void DDisplay(const std::string& message, T container)
{
    #ifdef DEBUG
    std::cout << message;
    if constexpr (std::is_same<typename T::value_type, std::pair<int, int>>::value)
    {
        for (const auto& pair : container)
            std::cout << "(" << pair.first << ", " << pair.second << ") ";
    }
    else
    {
        typename T::iterator it = container.begin();
        while (it != container.end() - 1)
        {
            std::cout << *it << " ";
            ++it;
        }
        std::cout << *it;
    }
    std::cout << "\n" << std::endl;
    #endif
    (void)message;
    (void)container;
}


#endif