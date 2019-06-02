/*
 *  test_union_find.cpp
 *  algorithm
 *
 *  Created by Bowen Liang.
 *
 */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctime>

#include "utils.hpp"

using std::cout;
using std::endl;
using namespace algorithm;

int main(int argc, char *argv[]) {
    cout<<"Test various sorting algorithms"<<endl;
    
    // first sort strings with selection sort
    std::vector<std::string> str_vectors;
    std::string filename = "/home/bowen/workspace/Algorithms/examples/input/words3.txt";
    FileReader::ReadFileWithAllStrs(filename, str_vectors);
    
    SortUtils::selectionSort<std::string>(str_vectors);
    for (int i = 0; i < str_vectors.size(); i++)
    {
        cout << str_vectors[i] << ", ";
    }
    cout<< endl;
    
    // then do a timing test for various sorting algoritms for random double vector of size N
    int N = 20000;
    
    // set seed for random number generator
    srand(1);
    std::vector<double> random_vecs, random_vecs1;
    random_vecs.reserve(N);
    for (int i=0; i<N; ++i)
    {
        random_vecs.push_back( (double) rand() / (RAND_MAX) );
    }
    
    // first use default sort function in C++ std
    random_vecs1 = random_vecs;
    std::clock_t start = std::clock();
    std::sort(random_vecs1.begin(), random_vecs1.end());
    double duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
    
    std::cout << "C++ STD sorting use time: " << duration << "s." << std::endl;
    
    // then use selection sort
    random_vecs1 = random_vecs;
    start = std::clock();
    SortUtils::selectionSort<double>(random_vecs1);
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
    
    std::cout << "Selection sorting use time: " << duration << "s." << std::endl;
    
    // then use shell sort with h = 3*x + 1
    random_vecs1 = random_vecs;
    start = std::clock();
    SortUtils::shellSort<double>(random_vecs1);
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
    
    std::cout << "Shell sorting use time: " << duration << "s." << std::endl;
    
    // then use merge sort
    random_vecs1 = random_vecs;
    start = std::clock();
    SortUtils::mergeSort<double>(random_vecs1);
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
    
    std::cout << "Merge sorting use time: " << duration << "s." << std::endl;
    
    // then use quick sort
    random_vecs1 = random_vecs;
    start = std::clock();
    SortUtils::quickSort<double>(random_vecs1);
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
    
    std::cout << "Quick sorting use time: " << duration << "s." << std::endl;

}