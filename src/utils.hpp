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
#include <set>
#include <unordered_map>

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

class Graph;

class FileReader
{
public:
    FileReader(){}
    ~FileReader(){}
    
    static void ReadFileWithAllInts(std::string const &filename, std::vector<int> &ints_vector);
    static void ReadFileWithAllInts(std::string const &filename, int &n, std::vector<int> &ints_vector_p, std::vector<int> &ints_vector_q);
    static void ReadFileWithAllStrs(std::string const &filename, std::vector<std::string> &str_vector);
    static Graph ReadFileToBuildGraph(std::string const &filename);

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

template <typename K, typename V>
class BinarySearchTree
{
public:
    BinarySearchTree() {}
    ~BinarySearchTree()
    {
        std::vector<Node*> queue;
        queue.push_back(m_root);
        while (!queue.empty())
        {
            auto it = queue.begin();
            Node *x = *it;
            queue.erase(it);
            
            if (x == NULL)
                continue;
                
            queue.push_back(x->left);
            queue.push_back(x->right);
            
            delete x;
        }     
    }
    
    struct Node
    {
        K key;
        V value;
        Node *left, *right;
        int size; // number of nodes in the subtree
    public:
        Node(K _key, V _value, int _size)
        : key(_key), value(_value), size(_size), left(NULL), right(NULL) {}
    }; 
    
    
    bool isEmpty()
    {
        return size() == 0;
    }
    
    int size()
    {
        return size(m_root);
    }
    
    bool contains(K key)
    {
        return !get(key).empty();
    }
    
    V get(K key)
    {
        return get(m_root, key);
    }
    
    void put(K key, V value)
    {
        m_root = put(m_root, key, value);
        assert(check());
    }
    
    void deleteMin()
    {
        assert(!isEmpty());
        m_root = deleteMin(m_root);
        assert(check());
    }
    
    void deleteMax()
    {
        assert(!isEmpty());
        m_root = deleteMax(m_root);
        assert(check());
    }
    
    void deleteKey(K key)
    {
        m_root = deleteKey(m_root);
        assert(check());
    }
    
    K minKey()
    {
        assert(!isEmpty());
        return minNode(m_root)->key;
    }
    
    K maxKey()
    {
        assert(!isEmpty());
        return maxNode(m_root)->key;
    }
    
    K floor(K key)
    {
        assert(!isEmpty());
        Node *x = floor(m_root, key);
        if (x == NULL)
            return NULL;
        else
            return x->key;
    }
    
    K ceiling(K key)
    {
        assert(!isEmpty());
        Node *x = ceiling(m_root, key);
        if (x == NULL)
            return NULL;
        else
            return x->key;
    }
    
    K select(int k)
    {
        assert(k >= 0 && k < size());
        Node *x = select(m_root, k);
        return x->key;
    }
    
    int rank(K key)
    {
        return rank(m_root, key);
    }
    
    int size(K lo, K hi)
    {
        if (lo > hi)
            return 0;
        if (contains(hi))
            return rank(hi) - rank(lo) + 1;
        else
            return rank(lo) - 1;
    }
    
    int height()
    {
        return height(m_root);
    }
    
    std::vector<K> levelOrder()
    {
        std::vector<K> keys;
        std::vector<Node*> queue;
        queue.push_back(m_root);
        while (!queue.empty())
        {
            auto it = queue.begin();
            Node *x = *it;
            queue.erase(it);
            
            if (x == NULL)
                continue;
                
            keys.push_back(x->key);
            queue.push_back(x->left);
            queue.push_back(x->right);
        }
        return keys;
    }
    
    std::vector<K> keys()
    {
        std::vector<K> all_keys;
        if (isEmpty())
            return all_keys;
        return keys(minKey(), maxKey());
    }
    
    std::vector<K> keys(K lo, K hi)
    {
        assert(!lo.empty() && !hi.empty());
        
        std::vector<K> all_keys;
        keys(m_root, all_keys, lo, hi);
        return all_keys;
    }
    
private:
    int size(Node *x)
    {
        if (x == NULL)
            return 0;
        else
            return x->size;
    }
    
    V get(Node *x, K key)
    {
        V emp;
        if (x == NULL)
            return emp;
            
        int cmp = key.compare(x->key);
        if (cmp < 0)
            return get(x->left, key);
        else if (cmp > 0)
            return get(x->right, key);
        else
            return x->value;
    }
    
    Node *put(Node *x, K key, V value)
    {
        if (x == NULL)
            return new Node(key, value, 1);
            
        int cmp = key.compare(x->key);
        if (cmp < 0)
            x->left = put(x->left, key, value);
        else if (cmp > 0)
            x->right = put(x->right, key, value);
        else
            x->value = value;
            
        x->size = 1 + size(x->left) + size(x->right);
        return x;
    }
    
    Node *deleteMin(Node *x)
    {
        if(x->left == NULL)
        {
            Node *x_right = x->right;
            delete x;
            return x_right;
        }
        
        x->left = deleteMin(x->left);
        x->size = size(x->left) + size(x->right) + 1;
        return x;
    }
        
    Node *deleteMax(Node *x)
    {
        if(x->right == NULL)
        {
            Node *x_left = x->left;
            delete x;
            return x_left;
        }
        
        x->right = deleteMin(x->right);
        x->size = size(x->left) + size(x->right) + 1;
        return x;
    }
    
    Node *deleteKey(Node *x, K key)
    {
        if (x == NULL)
            return NULL;
        
        int cmp = key.compare(x->key);
        if (cmp < 0)
            x->left = deleteKey(x->left, key);
        else if (cmp > 0)
            x->right = deleteKey(x->right, key);
        else
        {
            if (x->right == NULL)
            {
                Node *x_left = x->left;
                delete x;
                return x_left;
            }
            if(x->left == NULL)
            {
                Node *x_right = x->right;
                delete x;
                return x_right;
            }
            
            Node *tmp = x;
            x = minNode(tmp->right);
            x->right = deleteMin(tmp->right);
            x->left = tmp->left;
        }
        x->size = size(x->left) + size(x->right) + 1;
        return x;
    }
    
    Node *minNode(Node *x)
    {
        if(x->left == NULL)
            return x;
        return minNode(x->left);
    }
    
    Node *maxNode(Node *x)
    {
        if(x->right == NULL)
            return x;
        return minNode(x->right);
    }
    
    Node *floor(Node *x, K key)
    {
        if (x == NULL)
            return NULL;
        
        int cmp = key.compare(x->key);
        if (cmp == 0)
            return x;
        
        if (cmp < 0)
            return floor(x->left, key);
            
        Node *tmp = floor(x->right, key);
        if (tmp != NULL)
            return tmp;
        else
            return x;
    }
    
    Node *ceiling(Node *x, K key)
    {
        if (x == NULL)
            return NULL;
        
        int cmp = key.compare(x->key);
        if (cmp == 0)
            return x;
            
        if (cmp < 0)
        {
            Node *tmp = ceiling(x->left, key);
            if (tmp != NULL)
                return tmp;
            else
                return x;
        }
        
        ceiling(x->right, key);
    }
    
    Node *select(Node *x, int k)
    {
        if (x == NULL)
            return NULL;
        int t = size(x->left);
        if (t > k)
            return select(x->left, k);
        else if (t < k)
            return select(x->right, k - t - 1);
        else
            return x;
    }
    
    int rank(Node *x, K key)
    {
        if (x == NULL)
            return 0;
        int cmp = key.compare(x->key);
        if (cmp < 0)
            return rank(x->left, key);
        else if (cmp > 0)
            return 1 + size(x->left) + rank(x->right, key);
        else
            return size(x->left);
    }
    
    void keys(Node *x, std::vector<K> &all_keys, K lo, K hi)
    {
        if (x == NULL)
            return;
        int cmplo = lo.compare(x->key);
        int cmphi = hi.compare(x->key);
        
        if (cmplo < 0)
            keys(x->left, all_keys, lo, hi);
        if (cmplo <= 0 && cmphi >= 0)
            all_keys.push_back(x->key);
        if (cmphi > 0)
            keys(x->right, all_keys, lo, hi);
    }
    
    bool check()
    {
        K min, max;
        if(!isBST(m_root, min, max))
        {
            std::cout<<"Not in symmetric order! \n";
            return false;
        }
        if(!isSizeConsistent(m_root))
        {
            std::cout<<"Subtree counts not consistent! \n";
            return false;
        }
        if(!isRankConsistent())
        {
            std::cout<<"Ranks not consistent! \n";
            return false;
        }
        return true;
    }
    
    bool isBST(Node *x, K min, K max)
    {
        if (x == NULL)
            return true;
        
        if (!min.empty() && x->key.compare(min) <= 0)
            return false;
            
        if (!max.empty() && x->key.compare(max) >= 0)
            return false;
        
        return isBST(x->left, min, x->key) && isBST(x->right, x->key, max);
    }
    
    bool isSizeConsistent(Node *x)
    {
        if (x == NULL)
            return true;
            
        if (x->size != size(x->left) + size(x->right) + 1)
            return false;
            
        return isSizeConsistent(x->left) && isSizeConsistent(x->right);
    }
    
    bool isRankConsistent()
    {
        for (int i = 0; i < size(); i++)
        {
            if (i != rank(select(i)))
                return false;
        }
        return true;
    }

    Node *m_root = NULL;
};


template <typename K, typename V>
class RedBlackBST
{
public:
    RedBlackBST() {}
    ~RedBlackBST() 
    {
        std::vector<Node*> queue;
        queue.push_back(m_root);
        while (!queue.empty())
        {
            auto it = queue.begin();
            Node *x = *it;
            queue.erase(it);
            
            if (x == NULL)
                continue;
                
            queue.push_back(x->left);
            queue.push_back(x->right);
            
            delete x;
        }
    }
    
    struct Node
    {
        K key;
        V value;
        Node *left, *right;
        bool color;
    public:
        Node(K _key, V _value, bool _color)
        : key(_key), value(_value), color(_color), left(NULL), right(NULL) {}
    }; 
    
    V get(K key)
    {
        return get(m_root, key);
    }
    
    V get(Node *x, K key)
    {
        while (x != NULL)
        {
            int cmp = key.compare(x->key);
            if (cmp < 0)
                x = x->left;
            else if (cmp > 0)
                x = x->right;
            else 
                return x->value;
        }
        V v1;
        return v1;
    }
    
    bool contains(K key)
    {
        return !get(key).empty();
    }
    
    void put(K key, V value)
    {
        m_root = insert(m_root, key, value);
        m_root->color = BLACK;
        assert(check());
    }
    
    int size()
    {
        return n;
    }
    
    bool isEmpty()
    {
        return n == 0;
    }
    
    int height()
    {
        return height(m_root);
    }
    
    K minKey()
    {
        return minKey(m_root);
    }
    
    K maxKey()
    {
        return maxKey(m_root);
    }
    
    std::vector<K> keys()
    {
        std::vector<K> all_keys;
        keys(m_root, all_keys);
        return all_keys;
    }
    
    
private:
    Node *insert(Node *x, K key, V value)
    {
        if (x == NULL)
        {
            n++;
            return new Node(key, value, RED);
        }

        int cmp = key.compare(x->key);
        if (cmp < 0)
            x->left = insert(x->left, key, value);
        else if (cmp > 0)
            x->right = insert(x->right, key, value);
        else 
            x->value = value;
            
        // fix up and right-leaning links
        if (isRed(x->right) && !isRed(x->left))
            x = rotateLeft(x);
        if (isRed(x->left) && isRed(x->left->left))
            x = rotateRight(x);
        if (isRed(x->left) && isRed(x->right))
            flipColors(x);
            
        return x;
    }
    
    bool isRed(Node *x)
    {
        if (x == NULL)
            return false;
        return x->color == RED;
    }
    
    Node *rotateRight(Node *h)
    {
        assert(h != NULL && isRed(h->left));
        Node *x = h->left;
        h->left = x->right;
        x->right = h;
        x->color = h->color;
        h->color = RED;
        return x;
    }
    
    Node *rotateLeft(Node *h)
    {
        assert(h != NULL && isRed(h->right));
        Node *x = h->right;
        h->right = x->left;
        x->left = h;
        x->color = h->color;
        h->color = RED;
        return x;
    }
    
    void flipColors(Node *x)
    {
        assert(x != NULL && !isRed(x) && isRed(x->left) && isRed(x->right));
        x->color = RED;
        x->left->color = BLACK;
        x->right->color = BLACK;
    }
    
    int height(Node *x)
    {
        if (x == NULL)
            return -1;
            
        return 1 + std::max(height(x->left), height(x->right));
    }
    
    K minKey(Node *x)
    {
        K key;
        while (x != NULL)
        {
            key = x->key;
            x = x->left;
        }
        return key;
    }
    
    K maxKey(Node *x)
    {
        K key;
        while (x != NULL)
        {
            key = x->key;
            x = x->right;
        }
        return key;
    }
    
    void keys(Node *x, std::vector<K> &all_keys)
    {
        if (x == NULL)
            return;
        keys(x->left, all_keys);
        all_keys.push_back(x->key);
        keys(x->right, all_keys);
    }
    
    bool check()
    {
        K min, max;
        if (!isBST(m_root, min, max))
        {
            std::cout<<"Not in symmetric order! "<<std::endl;
            return false;
        }
        if (!is23(m_root))
        {
            std::cout<<"Not in 2-3 tree! "<<std::endl;
            return false;
        }
        if (!isBalanced())
        {
            std::cout<<"Not balanced! "<<std::endl;
            return false;
        }
        return true;
    }
    
    bool isBST(Node *x, K min, K max)
    {
        if (x == NULL)
            return true;
        if (!min.empty() && (x->key).compare(min) <= 0)
            return false;
        if (!max.empty() && (x->key).compare(max) >= 0)
            return false;
        return isBST(x->left, min, x->key) && isBST(x->right, x->key, max);
    }
    
    bool is23(Node *x)
    {
        if (x == NULL)
            return true;
        if (isRed(x->right))
            return false;
        if (x != m_root && isRed(x) && isRed(x->left))
            return false;
        return is23(x->right) && is23(x->right);
    }
    
    bool isBalanced()
    {
        int black = 0;
        Node *x = m_root;
        while (x != NULL)
        {
            if (!isRed(x))
                black++;
            x = x->left;
        }
        return isBalanced(m_root, black);
    }
    
    bool isBalanced(Node *x, int black)
    {
        if (x == NULL)
            return black == 0;
        if (!isRed(x))
            black--;
        return isBalanced(x->left, black) && isBalanced(x->right, black);
    }
    

    Node *m_root = NULL;
    int n;
    bool RED = true;
    bool BLACK = false;
};

template <typename K, typename V>
class HashSTSeparateChain
{
public:
    HashSTSeparateChain() 
    {
        size_n = 0;
        size_m = 997;
        st = new Node*[size_m](); // here () makes the node pointer is null as initialization
    }
    
    HashSTSeparateChain(int m) 
    {
        size_n = 0;
        size_m = m;
        st = new Node*[size_m]();        
    }
    
    ~HashSTSeparateChain() 
    {        
        for (int i = 0; i < size_m; i++)
        {
            Node *x = st[i];
            while (x != NULL)
            {
                Node *tmp = x->next;
                delete x;
                x = tmp;
            }
        }
        delete[] st;
    }
    
    struct Node
    {
        K key;
        V value;
        Node *next;

    public:
        Node(K _key, V _value, Node *_next)
        : key(_key), value(_value), next(_next) {}
    }; 
    
    int size()
    {
        return size_n;
    }
    
    bool isEmpty()
    {
        return size_n == 0;
    }
    
    bool contains(K key)
    {
        return !get(key).empty();
    }
    
    V get (K key)
    {
        int i = hash(key);
        for (Node *x = st[i]; x != NULL; x = x->next)
        {
            if (key.compare(x->key) == 0)
                return x->value;
        }
        V v1;
        return v1;
    }
    
    void put (K key, V val)
    {
        int i = hash(key);
        Node *x = st[i];
        for (; x != NULL; x = x->next)
        {
            if (key.compare(x->key) == 0)
            {
                x->value = val;
                return;
            }
        }
        size_n++;
        st[i] = new Node(key, val, st[i]);
    }
    
    std::vector<K> keys()
    {
        std::vector<K> queue;
        for (int i = 0; i < size_m; i++)
        {
            for (Node *x = st[i]; x != NULL; x = x->next)
            {
                queue.push_back(x->key);
            }
        }
        return queue;
    }
    
private:
    int hash(K key)
    {
        std::size_t hash_code = hasher(key);
        return (hash_code & 0x7fffffff) % size_m;
    }

    int size_n, size_m;
    Node **st;   
    std::hash<K> hasher;
    
};


template <typename K, typename V>
class HashSTLinearProbing
{
public:
    HashSTLinearProbing() 
    {
        size_n = 0;
        size_m = 4;
        m_keys = new K[size_m];
        m_values = new V[size_m];   
    }
    
    HashSTLinearProbing(int capacity) 
    {
        size_n = 0;
        size_m = capacity;
        m_keys = new K[size_m];
        m_values = new V[size_m];     
    }
    
    ~HashSTLinearProbing() 
    {        
        delete[] m_keys;
        delete[] m_values;
    }
    
    int size()
    {
        return size_n;
    }
    
    bool isEmpty()
    {
        return size_n == 0;
    }
    
    bool contains(K key)
    {
        return !get(key).empty();
    }
    
    V get (K key)
    {        
        for (int i = hash(key); !m_keys[i].empty(); i = (i+1)%size_m)
        {
            if (m_keys[i].compare(key) == 0)
            {
                return m_values[i];
            }
        }
        V v1;
        return v1;
    }
    
    void put (K key, V val)
    {
        if (size_n >= size_m / 2)
            resize(2*size_m);
            
        int i;
        for (i = hash(key); !m_keys[i].empty(); i = (i+1)%size_m)
        {
            if (m_keys[i].compare(key) == 0)
            {
                m_values[i] = val;
                return;
            }
        }
        size_n++;
        m_keys[i] = key;
        m_values[i] = val;
    }
    
    std::vector<K> keys()
    {
        std::vector<K> queue;
        for (int i = 0; i < size_m; i++)
        {
            if (!m_keys[i].empty())
            {
                queue.push_back(m_keys[i]);
            }
        }
        return queue;
    }
    
    K key_at(int i)
    {
        if (i < size_m)
            return m_keys[i];
        else
        {
            K k1;
            return k1;
        }
    }
    
    V value_at(int i)
    {
        if (i < size_m)
            return m_values[i];
        else
        {
            V v1;
            return v1;
        }
    }
    
private:
    int hash(K key)
    {
        std::size_t hash_code = hasher(key);
        return (hash_code & 0x7fffffff) % size_m;
    }
    
    void resize(int capacity)
    {
        HashSTLinearProbing<K, V> tmp(capacity);
        for (int i = 0; i < size_m; i++)
        {
            if (!m_keys[i].empty())
            {
                tmp.put(m_keys[i], m_values[i]);
            }
        }
        delete[] m_keys;
        delete[] m_values;
        
        m_keys = new K[capacity];
        m_values = new V[capacity];    
        for (int i = 0; i < capacity; i++)
        {
            if (!tmp.key_at(i).empty())
            {
                m_keys[i] = tmp.key_at(i);
                m_values[i] = tmp.value_at(i);
            }
        }
        
        size_m = capacity;
    }

    int size_n, size_m;
    K* m_keys;
    V* m_values;
    std::hash<K> hasher;
    
};


class Graph
{
public:
    Graph(int v);
    ~Graph();
    
    int V(){
        return num_V;
    }
    
    int E()
    {
        return num_E;
    }
    
    void addEdge(int v, int w);
    std::vector<int> adj(int v);
    int degree(int v);
    void print();
    
private:
    int num_V, num_E;
    std::vector<std::vector<int>> adj_vec;
};


__END_ALGORITHM__


#endif /* UTILS_HPP_ */
