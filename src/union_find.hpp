/*
 *  union_find.hpp
 *  algorithm
 *
 *  Created by Bowen Liang.
 *
 */


#ifndef UNION_FIND_HPP_
#define UNION_FIND_HPP_

#include "algorithm_fwd.hpp"

#include <math.h>
#include <algorithm>
#include <vector>
#include <string>

__BEGIN_ALGORITHM__

class UnionFind
{
public:
    UnionFind(int n);
    ~UnionFind() {}
    
    int find(int p);
    int count();
    bool connected(int p, int q);
    void connect (int p, int q);
    
private:
    bool validate(int p);
    
    std::vector<int> parent, rank;
    int m_count;    
};

class QuickFindUF
{
public:
    QuickFindUF(int n);
    ~QuickFindUF() {};
    
    int count();
    int find(int p);
    bool connected(int p, int q);
    void connect (int p, int q);
    
private:    
    bool validate(int p);
    
    std::vector<int> id;
    int m_count;    
};

__END_ALGORITHM__


#endif /* UNION_FIND_HPP_ */