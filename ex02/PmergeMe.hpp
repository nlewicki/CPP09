#ifndef PMERGEME_HPP
#define PMERGEME_HPP

class PmergeMe
{
    private:
        int method_idk_yet;
    
    public:
        PmergeMe();
        PmergeMe(const PmergeMe& source);
        PmergeMe& operator=(const PmergeMe& source);
        ~PmergeMe();

};


#endif