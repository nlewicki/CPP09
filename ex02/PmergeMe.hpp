#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <climits>
#include <algorithm>
#include <chrono>


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

        std::vector<int> getVector() const;
        std::deque<int> getDeque() const;
        void parseInput(int argc, char* argv[]);
        bool isValidNumber(const std::string& str) const;
        void exec();
        std::vector<int> sort_vector(std::vector<int>& vec);
        std::deque<int> sort_deque(std::deque<int>& deq);
};

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


#endif