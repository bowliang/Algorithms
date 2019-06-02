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

#include "union_find.hpp"
#include "utils.hpp"

using std::cout;
using std::endl;
using namespace algorithm;

int main(int argc, char *argv[]) {
    cout<<"Test union find functions"<<endl;
    
    std::vector<int> int_vectors_P, int_vectors_Q;
    int n;
    std::string filename = "/home/bowen/workspace/Algorithms/examples/input/mediumUF.txt";
    FileReader::ReadFileWithAllInts(filename, n, int_vectors_P, int_vectors_Q);
    
    // first test weighted union find
    std::clock_t start = std::clock();
    UnionFind uf(n);
    for (int i = 0; i < int_vectors_P.size(); i++)
    {
        int p = int_vectors_P[i];
        int q = int_vectors_Q[i];
        if (uf.connected(p, q))
            continue;
            
        uf.connect(p, q);
    }
    cout<< "Component:" << uf.count() <<endl;
    double duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
    
    std::cout << "Weighted UF use time: " << duration << "s." << std::endl;
    
    // now test quick find union find
    start = std::clock();
    QuickFindUF quick_find_UF(n);
    for (int i = 0; i < int_vectors_P.size(); i++)
    {
        int p = int_vectors_P[i];
        int q = int_vectors_Q[i];
        if (quick_find_UF.connected(p, q))
            continue;
            
        quick_find_UF.connect(p, q);
    }
    cout<< "Component:" << quick_find_UF.count() <<endl;
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
    
    std::cout << "Quick find UF use time: " << duration << "s." << std::endl;
}