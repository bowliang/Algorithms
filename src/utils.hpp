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

__END_ALGORITHM__


#endif /* UTILS_HPP_ */
