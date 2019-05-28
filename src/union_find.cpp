/*
 *  union_find.hpp
 *  algorithm
 *
 *  Created by Bowen Liang.
 *
 */

#include <iostream>

#include "algorithm_fwd.hpp"
#include "union_find.hpp"

#include<assert.h>

__BEGIN_ALGORITHM__


UnionFind::UnionFind(int n)
{
    assert(n >= 0);
    
    m_count = n;
    parent.resize(n);
    rank.resize(n);
    for (int i = 0; i < n; i++)
        parent[i] = i;            
}

int
UnionFind::find(int p)
{
    if(!validate(p))
        return 1;
    
    while (p != parent[p]) 
    {
        parent[p] = parent[parent[p]];
        p = parent[p];
    }
    
    return p;
}

int 
UnionFind::count()
{
    return m_count;
}

bool 
UnionFind::connected(int p, int q)
{
    return find(p) == find(q);
}

void 
UnionFind::connect(int p, int q)
{
    int rootP = find(p);
    int rootQ = find(q);
    if (rootP == rootQ) return;
    
    // make root of smaller rank point to root of larger rank
    if (rank[rootP] < rank[rootQ]) parent[rootP] = rootQ;
    else if (rank[rootP] > rank[rootQ]) parent[rootQ] = rootP;
    else
    {
        parent[rootP] = rootQ;
        rank[rootP]++;
    }
    m_count--;
}

bool 
UnionFind::validate(int p)
{
    if (p < 0 || p > parent.size())
        return false;
    return true;
}

__END_ALGORITHM__