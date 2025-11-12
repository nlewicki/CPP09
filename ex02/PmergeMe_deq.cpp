/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe_deq.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:56:04 by nlewicki          #+#    #+#             */
/*   Updated: 2025/11/12 13:51:13 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

static void  merge(std::deque<std::pair<int, int>>& pairs, int start, int end, int middle)
{
    int n1 = middle - start + 1;
    int n2 = end - middle;

    std::deque<std::pair<int, int>> left(pairs.begin() + start, pairs.begin() + start + n1);
    std::deque<std::pair<int, int>> right(pairs.begin() + middle + 1, pairs.begin() + middle + 1 + n2);

    int i = 0;
    int j = 0;
    int k = start;

    while (i < n1 && j < n2) 
    {
        if (left[i].second <= right[j].second)
            pairs[k++] = left[i++];  
        else
            pairs[k++] = right[j++];
    }
    
    while (i < n1)
        pairs[k++] = left[i++];
    while (j < n2)
        pairs[k++] = right[j++];
}

static void merge_sort(std::deque<std::pair<int, int>>& pairs, int start, int end)
{
    if (start < end)
    {
        int middle = start + (end - start) / 2;
        // sort left/right half recursively
        merge_sort(pairs, start, middle);
        merge_sort(pairs, middle + 1, end);
        // merge sorted pairs
        merge(pairs, start, end, middle);
    }
}

static void binary_insert(std::deque<int>& main, const int val, std::deque<int>::iterator R)
{
    std::deque<int>::iterator L = main.begin();

    while (L < R)
    {
        std::deque<int>::iterator mid = L + (R - L) / 2;
        if (val <= *mid)
            R = mid;
        else
            L = mid + 1;
    }
    main.insert(L, val);
}

static std::deque<int> get_insertion_order(int num_pairs, bool has_rest)
{
    std::deque<int> order;

    const int total_b = num_pairs + (has_rest ? 1 : 0);
    if (total_b <= 1)
        return order;

    std::deque<int> jacobsthal;
    jacobsthal.push_back(1);
    if (total_b >= 3)
        jacobsthal.push_back(3);
    
    while (jacobsthal.size() >= 2 && jacobsthal.back() < total_b)
    {
        int next = 2 * jacobsthal[jacobsthal.size() - 2] + jacobsthal.back();
        jacobsthal.push_back(next);
    }

    int prev = 1;
    
    for (size_t k = 1; k < jacobsthal.size(); k++)
    {
        int current = jacobsthal[k];
        if (current > total_b)
            current = total_b;
        for (int bj = current; bj > prev && bj >= 2; --bj)
            order.push_back(bj);
        
        if (current == total_b)
        {
            prev = current;
            break;
        }
        prev = jacobsthal[k];
    }

    if (prev < total_b)
    {
        for (int bj = total_b; bj > prev && bj >= 2; --bj)
            order.push_back(bj);
    }
    return order;
}


static void insertion_sort(std::deque<int> &main,
                    const std::deque<std::pair<int, int> > &pairs,
                    int rest)
{
    DDisplay("main (initial): ", main);
    DDisplay("pairs (pend): ", pairs);

    int num_pairs = static_cast<int>(pairs.size());
    bool has_rest = (rest != -1);

    std::deque<int> insertion_order = get_insertion_order(num_pairs, has_rest);
    DDisplay("insertion order (b_j indices): ", insertion_order);

    bool rest_inserted = false;
    
    for (size_t idx = 0; idx < insertion_order.size(); ++idx)
    {
        int j = insertion_order[idx];

        if (j >= 2 && j <= num_pairs)
        {
            const std::pair<int, int> &p = pairs[j - 1];
            std::deque<int>::iterator R =
                std::find(main.begin(), main.end(), p.second);
            binary_insert(main, p.first, R); 
        }
        else if (has_rest && j == num_pairs + 1 && !rest_inserted)
        {
            binary_insert(main, rest, main.end());
            rest_inserted = true;
            DDisplay_txt("Inserted odd element");
        }
    }
}


void PmergeMe::sort_deque()
{
    std::deque<std::pair<int, int> > pairs;
    std::deque<int> main;
    int rest = -1;

    if (_deque.size() % 2 != 0)
        rest = _deque.back();
    
    for (size_t i = 0; i + 1 < _deque.size(); i += 2)
    {
        int x = _deque[i];
        int y = _deque[i + 1];
        if (x > y)
            std::swap(x, y);
        pairs.push_back(std::make_pair(x, y));
    }

    DDisplay("Pairs before sorting: ", pairs);
    
    if (!pairs.empty())
    {
        merge_sort(pairs, 0, pairs.size() - 1);
        DDisplay("Pairs after sorting: ", pairs);

        main.push_back(pairs[0].first);
        for (size_t i = 0; i < pairs.size(); i++)
            main.push_back(pairs[i].second);

        insertion_sort(main, pairs, rest);
    }
    
    else if (rest != -1)
        main.push_back(rest);
        
    _deque.swap(main);
}