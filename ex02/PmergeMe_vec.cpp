/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe_vec.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:55:48 by nlewicki          #+#    #+#             */
/*   Updated: 2025/11/12 09:41:45 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void  merge(std::vector<std::pair<int, int>>& pairs, int start, int end, int middle)
{
    int n1 = middle - start + 1;
    int n2 = end - middle;

    std::vector<std::pair<int, int>> left(pairs.begin() + start, pairs.begin() + start + n1);
    std::vector<std::pair<int, int>> right(pairs.begin() + middle + 1, pairs.begin() + middle + 1 + n2);

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

void merge_sort(std::vector<std::pair<int, int>>& pairs, int start, int end)
{
    if (start < end)
    {
        int middle = start + (end - start) / 2;
        merge_sort(pairs, start, middle);
        merge_sort(pairs, middle + 1, end);
        merge(pairs, start, end, middle);
    }
}

// Insert val into main using binary search up to iterator R
// -> given order search in vector up to pair.second elements and insert
void binary_insert(std::vector<int>& main, const int val, std::vector<int>::iterator R)
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

std::vector<int> get_insertion_order(int num_pairs, bool has_rest)
{
    std::vector<int> order;

    const int total_b = num_pairs + (has_rest ? 1 : 0);
    if (total_b <= 1)
        return order;

    std::vector<int> jacobsthal;
    jacobsthal.push_back(1);
    if (total_b >= 3)
        jacobsthal.push_back(3);
    
    while (jacobsthal.size() >= 2 && jacobsthal.back() < total_b)
    {
        int next = 2 * jacobsthal[jacobsthal.size() - 1] + jacobsthal.back();
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


void insertion_sort(std::vector<int> &main,
                    const std::vector<std::pair<int, int> > &pairs,
                    int rest)
{
    DDisplay("main (initial): ", main);
    DDisplay("pairs (pend): ", pairs);

    int num_pairs = static_cast<int>(pairs.size());
    bool has_rest = (rest != -1);

    std::vector<int> insertion_order = get_insertion_order(num_pairs, has_rest);
    DDisplay("insertion order (b_j indices): ", insertion_order);

    bool rest_inserted = false;
    
    for (size_t idx = 0; idx < insertion_order.size(); ++idx)
    {
        int j = insertion_order[idx];

        // b_j gehört zu einem Paar
        if (j >= 2 && j <= num_pairs)
        {
            const std::pair<int, int> &p = pairs[j - 1]; // j ist 1-basiert
            std::vector<int>::iterator R =
                std::find(main.begin(), main.end(), p.second); // Position von a_j
            if (R == main.end())
            {
                // Sollte nicht passieren, aber falls doch: als Fallback ans Ende suchen
                R = main.end();
            }
            binary_insert(main, p.first, R);
        }
        // b_{num_pairs+1} repräsentiert das Rest-Element
        else if (has_rest && j == num_pairs + 1 && !rest_inserted)
        {
            binary_insert(main, rest, main.end());
            rest_inserted = true;
            std::cout << "insert odd element via sequence\n";
        }
    }

    // Falls rest aus irgendeinem Grund nicht in der Folge vorkam hinten einsortieren
    if (has_rest && !rest_inserted)
    {
        binary_insert(main, rest, main.end());
        std::cout << "inserted odd element at the end (fallback)\n";
    }
}


std::vector<int> PmergeMe::sort_vector(std::vector<int>& input)
{
    std::vector<std::pair<int, int> > pairs;
    std::vector<int> main;
    int rest = -1;

    if (input.size() % 2 != 0)
        rest = input.back();
    
    std::cout << "rest: " << rest << std::endl;
    //build pairs and sort each pair
    for (size_t i = 0; i + 1 < input.size(); i += 2)
    {
        int x = input[i];
        int y = input[i + 1];
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
        
    _vector = main;
    return main;
}