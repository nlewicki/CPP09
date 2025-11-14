/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe_vec.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:55:48 by nlewicki          #+#    #+#             */
/*   Updated: 2025/11/14 08:50:45 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


// sort pair by the second element
static void  merge(std::vector<std::pair<int, int>>& pairs, int start, int end, int middle)
{
    int n1 = middle - start + 1;
    int n2 = end - middle;

    std::vector<std::pair<int, int>> left(pairs.begin() + start, pairs.begin() + start + n1);
    std::vector<std::pair<int, int>> right(pairs.begin() + middle + 1, pairs.begin() + middle + 1 + n2);

    int i = 0;
    int j = 0;
    int k = start;

    while (i < n1 && j < n2) // while both subarrays have elements
    {
        if (left[i].second <= right[j].second) // compare by second element if left is smaller or equal
            pairs[k++] = left[i++]; // take from left 
        else
            pairs[k++] = right[j++]; // take from right
    }
    
    while (i < n1) // remaining elements in left
        pairs[k++] = left[i++]; // take from left
    while (j < n2) // remaining elements in right
        pairs[k++] = right[j++]; // take from right
}

static void merge_sort(std::vector<std::pair<int, int>>& pairs, int start, int end)
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

// Insert val into main using binary search up to iterator R
// -> given order search in vector up to pair.second elements and insert
static void binary_insert(std::vector<int>& main, const int val, std::vector<int>::iterator R)
{
    std::vector<int>::iterator L = main.begin();

    while (L < R)
    {
        std::vector<int>::iterator mid = L + (R - L) / 2;
        if (val <= *mid)
            R = mid;
        else
            L = mid + 1;
    }
    main.insert(L, val);
}

static std::vector<int> get_insertion_order(int num_pairs, bool has_rest)
{
    std::vector<int> order;

    // jacobsthal bekommen -> bis nicht mehr groeser geht
    const int total_b = num_pairs + (has_rest ? 1 : 0);
    if (total_b <= 1)
        return order;

    std::vector<int> jacobsthal;
    jacobsthal.push_back(1);
    if (total_b >= 3)
        jacobsthal.push_back(3);
    
    while (jacobsthal.size() >= 2 && jacobsthal.back() < total_b)
    {
        int next = 2 * jacobsthal[jacobsthal.size() - 2] + jacobsthal.back();
        jacobsthal.push_back(next);
    }

    //bei 1 anfangen
    int prev = 1;
    
    // bis letzte b checken (-> 3,2 -> 5,4 -> 11, 10, 9... bis current == total_b)
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

    // falls total_b 2, dann jacobsthal = 1, faellt hier rein
    if (prev < total_b)
    {
        for (int bj = total_b; bj > prev && bj >= 2; --bj)
            order.push_back(bj);
    }
    return order;
}


static void insertion_sort(std::vector<int> &main,
                    const std::vector<std::pair<int, int> > &pairs,
                    int rest)
{
    DDisplay("main (initial): ", main);
    DDisplay("pairs (pend): ", pairs);

    int num_pairs = static_cast<int>(pairs.size());
    bool has_rest = (rest != -1);

    std::vector<int> insertion_order = get_insertion_order(num_pairs, has_rest); // bsp order 3 2 4 => heist erst b3, dann b2, dann b4
    DDisplay("insertion order (b_j indices): ", insertion_order);

    bool rest_inserted = false;
    
    for (size_t idx = 0; idx < insertion_order.size(); ++idx)
    {
        int j = insertion_order[idx];

        if (j >= 2 && j <= num_pairs)
        {
            const std::pair<int, int> &p = pairs[j - 1];
            std::vector<int>::iterator R =
                std::find(main.begin(), main.end(), p.second);
            binary_insert(main, p.first, R); // zahl einfuegen
        }
        else if (has_rest && j == num_pairs + 1 && !rest_inserted) // rest einfuegen falls vorhanden
        {
            binary_insert(main, rest, main.end());
            rest_inserted = true;
            DDisplay_txt("Inserted odd element");
        }
    }
}


void PmergeMe::sort_vector()
{
    std::vector<std::pair<int, int> > pairs;
    std::vector<int> main;
    int rest = -1;

    if (_vector.size() % 2 != 0)
        rest = _vector.back();
    
    // std::cout << "rest: " << rest << std::endl;
    //build pairs and sort each pair
    for (size_t i = 0; i + 1 < _vector.size(); i += 2)
    {
        int x = _vector[i];
        int y = _vector[i + 1];
        if (x > y)
            std::swap(x, y);
        pairs.push_back(std::make_pair(x, y));
    }

    DDisplay("Pairs before sorting: ", pairs);
    
    //if pairs, sort pairs with merge sort and build main sequence
    if (!pairs.empty())
    {
        merge_sort(pairs, 0, pairs.size() - 1);
        DDisplay("Pairs after sorting: ", pairs);

        main.push_back(pairs[0].first);
        for (size_t i = 0; i < pairs.size(); i++)
            main.push_back(pairs[i].second);

        // insert the first elements of each pair into main using binary insertion (main: b1, a1, a2, a3,...)
        insertion_sort(main, pairs, rest);
    }
    
    //if there's a leftover element, insert it into main
    else if (rest != -1)
        main.push_back(rest);
        
    _vector.swap(main);
}