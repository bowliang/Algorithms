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
        return -1;
    
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
    if(!validate(p) || !validate(q))
        return false;
        
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


QuickFindUF::QuickFindUF(int n)
{    
    assert(n >= 0);
    
    m_count = n;
    id.resize(n);
    for (int i = 0; i < n; i++)
        id[i] = i;      
    
}

int 
QuickFindUF::count()
{
    return m_count;
}

int 
QuickFindUF::find(int p)
{
    if(!validate(p))
        return -1;
    
    return id[p];
}

bool 
QuickFindUF::connected(int p, int q)
{
    if(!validate(p) || !validate(q))
        return false;
        
    return id[p] == id[q];
}

void 
QuickFindUF::connect (int p, int q)
{
    if(!validate(p) || !validate(q))
        return;
        
    int pID = id[p];
    int qID = id[q];
    
    if (pID == qID)
        return;
        
    for (int i = 0; i < id.size(); i++)
    {
        if (id[i] == pID)
            id[i] = qID;            
    }
    m_count--;
}

bool 
QuickFindUF::validate(int p)
{
    if (p < 0 || p > id.size())
        return false;
    return true;
}


__END_ALGORITHM__