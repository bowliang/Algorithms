/*
 *  math.hpp
 *  algorithm
 *
 *  Created by Bowen Liang.
 *
 */


#ifndef UTILS_HPP_
#define UTILS_HPP_

#include "algorithm_fwd.hpp"

#include <math.h>
#include <assert.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

__BEGIN_ALGORITHM__

/*This is binary search class to look the index of number in a sorted array*/
template <typename T>
int BinarySearchRank(T k, std::vector<T> const &a)
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
    
    static void ReadFileWithAllInts(std::string const &filename, std::vector<int> &ints_vector);
    static void ReadFileWithAllInts(std::string const &filename, int &n, std::vector<int> &ints_vector_p, std::vector<int> &ints_vector_q);
    static void ReadFileWithAllStrs(std::string const &filename, std::vector<std::string> &str_vector);

};

template <typename T>
struct Node
{
    T value;
    Node *next;
};

template <typename T>
class SingleLinkedList
{
public:
    SingleLinkedList()
    {
        head = nullptr;
        tail = nullptr;
        length_list = 0;
    }
    
    ~SingleLinkedList()
    {
        // free the allocation
        Node<T> *tmp = head;
        while (tmp != nullptr)
        {
            head = head->next;
            delete tmp;
            tmp = head;
        }
        head = nullptr;
        tail = nullptr;        
    }
    
    void AddNode(T value)
    {
        Node<T> *tmp = new Node<T>;
        tmp->value = value;
        tmp->next = nullptr;
        
        if (head == nullptr)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tmp;
        }
        length_list++;
    }
    
    void AddAtFront(T value)
    {
        Node<T> *tmp = new Node<T>;
        tmp->value = value;
        tmp->next = head;
        head = tmp;
        length_list++;
    }
    
    void AddAtBack(T value)
    {
        AddNode(value);
    }
    
    void AddAtPos(T value, int pos)
    {
        if (pos < 0 || pos >= length_list)
        {
            std::cout<< "Invalid insert position \n";
            return;
        }
        
        if (pos == 0)
        {
            AddAtFront(value);
            return;
        }
        else if (pos == length_list - 1)
        {
            AddAtBack(value);
            return;
        }
        
        Node<T> *pre = head, *cur = head->next;
        for (int i = 1; i < pos; i++)
        {          
            pre = cur;
            cur = cur->next;
        }
        
        Node<T> *tmp = new Node<T>;
        tmp->value = value;
        tmp->next = cur;
        pre->next = tmp;
        length_list++;      
        
    }
    
    void RemoveAtFront()
    {
        if (length_list == 0)
        {
            std::cout << "Cannot remove anything from empty list\n";
            return;
        }
        else if (length_list == 1)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            Node<T>* tmp = head;
            head = head->next;
            delete tmp;
        }        
        length_list--;
    }
    
    void RemoveAtBack()
    {
        if (length_list == 0)
        {
            std::cout << "Cannot remove anything from empty list\n";
            return;
        }
        else if (length_list == 1)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            Node<T>* tmp = tail;
            // now find the node previous of tail
            Node<T>* tmp1 = head;
            while(tmp1->next != tmp)
            {
                tmp1 = tmp1->next;
            }
            tail = tmp1;
            tail->next = nullptr;
            delete tmp;
        }        
        length_list--;
    }
    
    void RemoveAtPos(int pos)
    {
        if (pos < 0 || pos >= length_list)
        {
            std::cout << "Invalid pos index\n";
            return;
        }
        
        if (pos == 0 || length_list == 1)
        {
            RemoveAtFront();
            return;
        }
        else if (pos == length_list - 1)
        {
            RemoveAtBack();
            return;
        }
        
        Node<T> *pre = head, *cur = head->next;
        for (int i = 1; i < pos; i++)
        {          
            pre = cur;
            cur = cur->next;
        }
        
        pre->next = cur->next;
        delete cur;
        length_list--;  
        
    }
    
    void Display()
    {
        Node<T> *tmp = head;
        while (tmp != nullptr)
        {
            std::cout<< tmp->value << "\t";
            tmp = tmp->next;
        }
        std::cout<< "\n";
    }
    
    int Size()
    {
        return length_list;
    }
    
private:
    Node<T> *head, *tail;  
    int length_list;
};


template <typename T>
class PriorityQueue
{
public:
    PriorityQueue(int capacity)
    {
        m_pq.reserve(capacity+1);
        n = 0;
    }
    
    PriorityQueue()
    {
        m_pq.reserve(1);
        n = 0;
    }
    
    PriorityQueue(std::vector<T> &pq)
    {
        n = pq.size();
        m_pq.resize(n + 1);
        for (int i = 0; i < n; i++)
            m_pq[i + 1] = pq[i];
        for (int i = n / 2; i >= 1; i--)
            sink(i);
    }
    
    ~PriorityQueue() {};
    
    bool isEmpty()
    {
        return n == 0;
    }
    
    int size()
    {
        return n;
    }
    
    T max()
    {
        assert(!isEmpty());
        return m_pq[1];
    }
    
    void insert(T value)
    {
        if (n == m_pq.size() - 1)
            resize(2 * m_pq.size());
        
        m_pq[++n] = value;
        swim(n);
        assert(isMaxHeap());
    }
    
    T delMax()
    {
        assert(!isEmpty());
        
        T max = m_pq[1];
        std::swap(m_pq[1], m_pq[n--]);
        sink(1);
        if ((n > 0) && (n == (m_pq.size() - 1) / 4))
            resize(m_pq.size() / 2);
            
        assert(isMaxHeap());
        return max;
    }
    
    void display()
    {
        for (int i = 1; i <= n; i++)
        {
            std::cout<< m_pq[i] << "\t";
        }
        std::cout<< "\n";        
    }
    
    void swap(int i, int j)
    {
        assert(i <= n && i >= 1 && j <= n && j >= 1);
        std::swap(m_pq[i], m_pq[j]);
    }
    
private:
    void resize(int capacity)
    {
        assert(capacity > n);
        std::vector<T> tmp = m_pq;
        m_pq.clear();
        m_pq.resize(capacity + 1);
        for (int i = 0; i < n; i++)
            m_pq[i + 1] = tmp[i + 1]; 
    }
    
    void sink(int k)
    {
        while (2 * k < n)
        {
            int j = 2 * k;
            if (j < n && m_pq[j] < m_pq[j+1])
                j++;
            if(m_pq[k] >= m_pq[j])
                break;
            std::swap(m_pq[k], m_pq[j]);
            k = j;
        }
    }
    
    void swim(int k)
    {
        while (k > 1 && m_pq[k / 2] < m_pq[k])
        {
            std::swap(m_pq[k], m_pq[k / 2]);
            k = k / 2;
        }
    }
    
    bool isMaxHeap()
    {
        return isMaxHeap(1);
    }
    
    bool isMaxHeap(int k)
    {
        if (k > n)
            return true;
        int left = k * 2;
        int right = left + 1;
        if(left < n && m_pq[k] < m_pq[left])
            return false;
        if(right < n && m_pq[k] < m_pq[right])
            return false;
        return isMaxHeap(left) && isMaxHeap(right);
    }


    std::vector<T> m_pq;
    int n;
    
};


class BasicUtils
{
public:
    BasicUtils(){}
    ~BasicUtils(){}
    
    static int TwoSumBrute(std::vector<int> &ints_vector);
    static int TwoSumFast(std::vector<int> &ints_vector);
    static int ThreeSumBrute(std::vector<int> &ints_vector);
    static int ThreeSumFast(std::vector<int> &ints_vector);
};

class SortUtils
{
public:
    SortUtils(){}
    ~SortUtils(){}
    
    template <typename T>
    static bool isSorted(std::vector<T> &vector_vals, int lo, int hi)
    {
        for (int i = lo + 1; i <= hi; i++)
        {
            if (vector_vals[i] < vector_vals[i-1])
                return false;
        }
        return true;
    }
    
    template <typename T>
    static bool isSorted(std::vector<T> &vector_vals)
    {
        return isSorted(vector_vals, 0, vector_vals.size() - 1);
    }
    
    template <typename T>
    static bool isHSorted(std::vector<T> &vector_vals, int h)
    {
        for (int i = h; i < vector_vals.size(); i++)
        {
            if (vector_vals[i] < vector_vals[i-h])
                return false;
        }
        return true;
    }
    
    template <typename T>
    static void selectionSort(std::vector<T> &vector_vals)
    {
        int n = vector_vals.size();
        for (int i = 0; i < n; i++)
        {
            int min = i;
            for (int j = i + 1; j < n; j++)
            {
                if (vector_vals[j] < vector_vals[min])
                    min = j;
            }
            std::swap(vector_vals[i], vector_vals[min]);
            assert(isSorted<T>(vector_vals, 0, i));
        }
        assert(isSorted<T>(vector_vals));
    }
    
    template <typename T>
    static void shellSort(std::vector<T> &vector_vals)
    {
        int n = vector_vals.size();
        
        // 3x + 1 incremental sequence for h-sorting
        int h = 1;
        while (h < n / 3)
            h = h * 3 + 1;
            
        while (h >= 1)
        {
            // h-sort the vector
            for (int i = h; i < n; i++)
            {
                for (int j = i; j >= h && vector_vals[j] < vector_vals[j - h]; j -= h)
                    std::swap(vector_vals[j], vector_vals[j - h]);
            }
            assert(isHSorted<T>(vector_vals, h));
            h /= 3;
        }
        assert(isSorted<T>(vector_vals));        
    }
    
    template <typename T>
    static void mergeSort(std::vector<T> &vector_vals)
    {
        std::vector<T> vector_aux = vector_vals;
        mergeSort<T>(vector_vals, vector_aux, 0, vector_vals.size()-1);
        assert(isSorted<T>(vector_vals));        
    }
    
    template <typename T>
    static void quickSort(std::vector<T> &vector_vals)
    {
        std::random_shuffle(vector_vals.begin(), vector_vals.end());
        quickSort<T>(vector_vals, 0, vector_vals.size()-1);
        assert(isSorted<T>(vector_vals));        
    }
    
    template <typename T>
    static void heapSort(std::vector<T> &vector_vals)
    {
        int n = vector_vals.size();
        for (int k = n / 2; k >= 1; k--)
            sink(vector_vals, k, n);
        while (n > 1)
        {
            exch(vector_vals, 1, n--);
            sink(vector_vals, 1, n);
        }
        assert(isSorted<T>(vector_vals));        
    }
    
private:
    template <typename T>
    static void mergeSort(std::vector<T> &vector_vals, std::vector<T> &vector_aux, int lo, int hi)
    {
        if (hi <= lo)
            return;
            
        int mid = lo + (hi - lo) / 2;
        mergeSort(vector_vals, vector_aux, lo, mid);
        mergeSort(vector_vals, vector_aux, mid + 1, hi);
        merge(vector_vals, vector_aux, lo, mid, hi);
    }
    
    template <typename T>
    static void merge(std::vector<T> &vector_vals, std::vector<T> &vector_aux, int lo, int mid, int hi)
    {
        assert(isSorted<T>(vector_vals, lo, mid));  
        assert(isSorted<T>(vector_vals, mid + 1, hi));  
        
        for (int i = lo; i <= hi; i++)
        {
            vector_aux[i] = vector_vals[i];
        }
        
        int i = lo, j = mid + 1;
        for (int k = lo; k <= hi; k++)
        {
            if (i > mid)
                vector_vals[k] = vector_aux[j++];
            else if (j > hi)
                vector_vals[k] = vector_aux[i++];
            else if (vector_aux[i] < vector_aux[j])
                vector_vals[k] = vector_aux[i++];
            else
                vector_vals[k] = vector_aux[j++];
        }
    }
    
    template <typename T>
    static void quickSort(std::vector<T> &vector_vals, int lo, int hi)
    {
        if (hi <= lo)
            return;
            
        int j = partition(vector_vals, lo, hi);
        quickSort(vector_vals, lo, j-1);
        quickSort(vector_vals, j+1, hi);
        assert(isSorted<T>(vector_vals, lo, hi));
    }
    
    template <typename T>
    static int partition(std::vector<T> &vector_vals, int lo, int hi)
    {
        int i = lo;
        int j = hi + 1;
        T v = vector_vals[lo];
        while(true)
        {
            while(vector_vals[++i] < v)
            {
                if (i == hi)
                    break;
            }
            
            while(v < vector_vals[--j])
            {
                if (j == lo)
                    break;
            }
            
            if (i >= j)
                break;
                
            std::swap(vector_vals[i], vector_vals[j]);
        }
        
        std::swap(vector_vals[lo], vector_vals[j]);
        return j;
    }
    
    template <typename T>
    static void sink(std::vector<T> &vector_vals, int k, int n)
    {
        while(2*k <= n)
        {
            int j = 2*k;
            if (j < n && less(vector_vals, j, j+1))
                j++;
            if (!less(vector_vals, k, j))
                break;
            exch(vector_vals, k, j);
            k = j;
        }
    }
    
    template <typename T>
    static void exch(std::vector<T> &vector_vals, int i, int j)
    {
        // indices are "off-by-one" for heap sort
        std::swap(vector_vals[i - 1], vector_vals[j - 1]);
    }
    
    template <typename T>
    static bool less(std::vector<T> &vector_vals, int i, int j)
    {
        // indices are "off-by-one" for heap sort
        return (vector_vals[i - 1] < vector_vals[j - 1]);
    }
    
};

__END_ALGORITHM__


#endif /* UTILS_HPP_ */
