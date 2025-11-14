#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>
#include <cctype>

class RPN {
    private:
        std::stack<int> _operand;

    public:
        RPN();
        RPN(const RPN& source);
        RPN& operator=(const RPN& source);
        ~RPN();

        int evaluate(const std::string& expression);
        int performOperation(int lhs, int rhs, char op);
};

#endif