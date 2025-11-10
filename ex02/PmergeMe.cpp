/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:04:30 by nlewicki          #+#    #+#             */
/*   Updated: 2025/11/10 10:10:15 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
    
}

PmergeMe::PmergeMe(const PmergeMe& source)
{
    *this = source;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& source)
{
    if (this != &source)
        *this = source;
    return *this;
}

PmergeMe::~PmergeMe()
{
    
}
