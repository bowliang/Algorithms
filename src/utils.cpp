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

void 
FileReader::ReadFileWithAllStrs(std::string const &filename, std::vector<std::string> &str_vector)
{
    std::ifstream myfile;
    std::string line, token;
    std::string delimiter = " ";
    myfile.open(filename.c_str());
    if (myfile)
    {        
        std::size_t pos = 0;
        while (std::getline(myfile, line))
        {
            while ((pos = line.find(delimiter)) != std::string::npos)
            {
                token = line.substr(0, pos);
                str_vector.push_back(token);
                line.erase(0, pos + delimiter.length());
            }
            str_vector.push_back(line);
        }
        myfile.close();
    }
    else
    {
        std::cout << "File " << filename << " not found! \n";
    }
}

Graph 
FileReader::ReadFileToBuildGraph(std::string const &filename)
{
    std::ifstream myfile;
    std::string line, token;
    std::string delimiter = " ";
    myfile.open(filename.c_str());
    if (myfile)
    {        
        std::getline(myfile, line);
        int num_V = std::stoi(line);
        std::getline(myfile, line);
        int num_E = std::stoi(line);
        
        Graph graph(num_V);
        
        std::size_t pos = 0;
        int v, w;
        while (std::getline(myfile, line))
        {
            while ((pos = line.find(delimiter)) != std::string::npos)
            {
                token = line.substr(0, pos);
                v = std::stoi(token);
                line.erase(0, pos + delimiter.length());
            }
            w = std::stoi(line);
            graph.addEdge(v, w);
        }
        myfile.close();
        return graph;
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

Graph::Graph(int v)
{
    assert(v >= 0);
    num_V = v;
    num_E = 0;
    adj_vec.resize(num_V);
}

Graph::~Graph()
{
    
}

void 
Graph::addEdge(int v, int w)
{
    num_E++;
    adj_vec[v].push_back(w);
    adj_vec[w].push_back(v);
}
    
std::vector<int> 
Graph::adj(int v)
{
    return adj_vec[v];
}

int 
Graph::degree(int v)
{
    return adj_vec[v].size();
}

void 
Graph::print()
{
    std::cout<<num_V<<" vertices, "<<num_E<<" edges \n";
    for (int i = 0; i < num_V; i++)
    {
        std::cout<<i<<": ";
        for (auto w : adj_vec[i])
        {
            std::cout<<w<<" ";
        }
        std::cout<<"\n";
    }
}


DepthFirstSearch::DepthFirstSearch(Graph G, int s)
{
    source = s;
    marker.resize(G.V());
    edgeTo.resize(G.V());
    assert(s>=0 && s <G.V());
    dfs(G, s);
}
    
bool 
DepthFirstSearch::marked(int v)
{
    assert(v>=0 && v < marker.size());
    return marker[v];
}

int 
DepthFirstSearch::count()
{
    return counter;
}

bool 
DepthFirstSearch::hasPathTo(int v)
{
    return marker[v];
}

std::vector<int> 
DepthFirstSearch::pathTo(int v)
{
    std::vector<int> path;
    if (!hasPathTo(v))
        return path;
        
    for(int x = v; x != source; x = edgeTo[x])
        path.push_back(x);
    path.push_back(source);
    
    return path;
}
    
    
void
DepthFirstSearch::dfs(Graph G, int v)
{
    counter++;
    marker[v] = true;
    for (auto w : G.adj(v))
    {
        if (!marker[w])
        {
            edgeTo[w] = v;
            dfs(G, w);
        }            
    }
}


__END_ALGORITHM__
