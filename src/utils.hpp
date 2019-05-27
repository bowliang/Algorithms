/*
 *  math.hpp
 *  algorithm
 *
 *  Created by Bowen Liang.
 *
 */


#ifndef MATH_HPP_
#define MATH_HPP_

#include "algorithm_fwd.hpp"

#include <math.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

__BEGIN_ALGORITHM__
/*This is binary search class to look the index of number in a sorted array*/
template <class R>
int BinarySearchRank(R k, std::vector<R> const &a)
{
    int lo = 0, hi = a.size() - 1;
    while (lo <= hi)
    {
        int mid = lo + (hi - lo)/2;
        if (k < a[mid]) hi = mid -1;
        else if (k > a[mid]) lo = mid + 1;
        else return mid;
    }
    return -1;
}

class FileReader
{
public:
    FileReader(){}
    ~FileReader(){}
    
    static void ReadFileWithAllInts(std::string const &filename, std::vector<int> &ints_vector)
    {
        std::ifstream myfile;
        std::string line;
        myfile.open(filename.c_str());
        if (myfile)
        {
            while (std::getline(myfile, line))
            {
                int value = std::stoi(line);
                ints_vector.push_back(value);                
            }
            myfile.close();
        }
        else
        {
            std::cout << "File " << filename << " not found! \n";
        }
    }
};

__END_ALGORITHM__


#endif /* MATH_HPP_ */
