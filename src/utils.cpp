/*
 *  math.hpp
 *  algorithm
 *
 *  Created by Bowen Liang.
 *
 */


#include "algorithm_fwd.hpp"
#include "utils.hpp"

__BEGIN_ALGORITHM__
void 
FileReader::ReadFileWithAllInts(std::string const &filename, std::vector<int> &ints_vector)
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

void 
FileReader::ReadFileWithAllInts(std::string const &filename, int &n, std::vector<int> &ints_vector_p, std::vector<int> &ints_vector_q)
{
    std::ifstream myfile;
    std::string line, token;
    std::string delimiter = " ";
    myfile.open(filename.c_str());
    if (myfile)
    {
        std::getline(myfile, line);
        n = std::stoi(line);
        ints_vector_p.reserve(n);
        ints_vector_q.reserve(n);
        
        while (std::getline(myfile, line))
        {
            std::size_t pos = line.find(delimiter);
            token = line.substr(0, pos);
            ints_vector_p.push_back(std::stoi(token));
            line.erase(0, pos + delimiter.length());
            ints_vector_q.push_back(std::stoi(line));                         
        }
        myfile.close();
    }
    else
    {
        std::cout << "File " << filename << " not found! \n";
    }
}

int 
BasicUtils::TwoSumBrute(std::vector<int> &ints_vector)
{
    int n = ints_vector.size();
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (ints_vector[i] + ints_vector[j] == 0)
                count++;
        }
    }
    return count;
}

int 
BasicUtils::TwoSumFast(std::vector<int> &ints_vector)
{
    int n = ints_vector.size();
    int count = 0;
    std::sort(ints_vector.begin(), ints_vector.end());
    for (int i = 0; i < n; i++)
    {
        int index = BinarySearchRank<int>(-ints_vector[i], ints_vector);
        if (index > i)
            count++;
    }
    return count;
}

int 
BasicUtils::ThreeSumBrute(std::vector<int> &ints_vector)
{
    int n = ints_vector.size();
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            for (int k = j+1; k < n; k++)
            {
                if (ints_vector[i] + ints_vector[j] + ints_vector[k] == 0)
                    count++;
            }
        }
    }
    return count;
}

int 
BasicUtils::ThreeSumFast(std::vector<int> &ints_vector)
{
    int n = ints_vector.size();
    int count = 0;
    std::sort(ints_vector.begin(), ints_vector.end());
    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            int index = BinarySearchRank<int>(-(ints_vector[i]+ints_vector[j]), ints_vector);
            if (index > j)
                count++;
        }
        
    }
    return count;
}

__END_ALGORITHM__
