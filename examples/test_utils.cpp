/*
 *  test_math.cpp
 *  cpputils
 *
 *  Created by Bowen Liang.
 *
 */

#include <iostream>
#include <stdlib.h>
#include <string>

#include "utils.hpp"

using std::cout;
using std::endl;
using namespace algorithm;

int main(int argc, char *argv[]) {
    cout<<"Test utility functions"<<endl;
    
    // set seed for random number generator
    srand(1);
    std::vector<int> random_vecs;
    random_vecs.reserve(100);
    for (int i=0; i<100; ++i)
    {
        random_vecs.push_back(rand() % 100);
    }
    std::sort(random_vecs.begin(), random_vecs.end());
    for (int i=0; i<20; ++i)
    {
        int key = rand() % 100;
        int index = BinarySearchRank<int>(key, random_vecs);
        if (index > -1)
            std::cout << "Key " << key << " found with id " << index << std::endl;
        else
            std::cout << "Key " << key << " not found! "<< std::endl;
    }
    
    // white list and black list two sets of text files
    std::vector<int> int_vectors_T, int_vectors_W;
    std::string filename_T = "/home/bowen/workspace/Algorithms/examples/input/tinyT.txt";
    std::string filename_W = "/home/bowen/workspace/Algorithms/examples/input/tinyW.txt";
    FileReader::ReadFileWithAllInts(filename_T, int_vectors_T);
    FileReader::ReadFileWithAllInts(filename_W, int_vectors_W);

    std::cout << "************************************************************" << std::endl;
    std::cout << "Begin whilte list" << std::endl;
    
    std::sort(int_vectors_W.begin(), int_vectors_W.end());
    for (auto key : int_vectors_T)
    {
        int index = BinarySearchRank<int>(key, int_vectors_W);
        if (index < 0)
            std::cout << "Key " << key << " not found! "<< std::endl;
    }
    

    return 0;
}
