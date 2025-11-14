/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:16:29 by nlewicki          #+#    #+#             */
/*   Updated: 2025/11/14 09:06:30 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
    
}

RPN::RPN(const RPN& source)
{
    *this = source; 
}

RPN& RPN::operator=(const RPN& source)
{
    if(this != &source)
        *this = source;
    return *this;
}

RPN::~RPN()
{
    
}


int RPN::performOperation(int lhs, int rhs, char op)
{
    switch (op)
    {
        case '+': return lhs + rhs;
        case '-': return lhs - rhs;
        case '*': return lhs * rhs;
        case '/':
            if (rhs == 0) throw std::runtime_error("division by zero");
            return lhs / rhs;
    }
    throw std::runtime_error("unknown operator");
}

int RPN::evaluate(const std::string& expression)
{
    std::stack<int> stack;
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token)
    {
        if (token.size() == 1 && token[0] >= '0' && token[0] <= '9')
            stack.push(token[0] - '0');
        else if (token.size() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/'))
        {
            if (stack.size() < 2) throw std::runtime_error("not enough operands");
            int rhs = stack.top(); // holt den obersten Wert
            stack.pop(); // loescht nur obersten Wert
            int lhs = stack.top();
            stack.pop();
            stack.push(performOperation(lhs, rhs, token[0]));
        }
        else
            throw std::runtime_error("invalid token: '" + token + "'");
    }
    if (stack.size() != 1)
        throw std::runtime_error("too many operands");
    return (stack.top());
}