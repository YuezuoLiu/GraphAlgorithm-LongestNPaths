#ifndef CPP_PROGRAM_ASSIGNMENT1_INCLUDE_GRAPH_HH_
#define CPP_PROGRAM_ASSIGNMENT1_INCLUDE_GRAPH_HH_

#include <vector>
#include "Utils.hh"

class Graph
{
public:
    Graph()
    {
        _adjacent_matrix = nullptr;
        _indegrees = nullptr;
        _valid = nullptr;
    }

    ~Graph();

    void showMatrix()
    {
        for (int i = 0; i < _vertex_num; ++i)
        {
            for (int j = 0; j < _vertex_num; ++j)
                printf("%d ", _adjacent_matrix[i][j]);
            printf("\n");
        }
    }

    void showIndegree()
    {
        printf("Indegrees: ");
        for (int i = 0; i < _vertex_num; ++i)
            printf("%d ", _indegrees[i]);
        printf("\n");
    }

    void makeGraph();

    void initiateTraverseData();

    void traverse(int n);

private:
    int findZeroIndegreeVertex()
    {
        for (int i = 0; i < _vertex_num; ++i)
            if (_valid[i] && _indegrees[i] == 0)
                return i;
        return -1;
    }

    void updateIndegreeArray(int out_vertex_index)
    {
        for (int i = 0; i < _vertex_num; ++i)
            if (_adjacent_matrix[out_vertex_index][i] != 0)
                --_indegrees[i];
    }

    std::vector<int> getSuccessors(int vertex_index)
    {
        std::vector<int> successors;
        for (int i = 0; i < _vertex_num; ++i)
            if (_adjacent_matrix[vertex_index][i] != 0)
                successors.push_back(i);
        return successors;
    }

    std::vector<int> getPredecessors(int vertex_index)
    {
        std::vector<int> predecessors;
        for (int i = 0; i < _vertex_num; ++i)
            if (_adjacent_matrix[i][vertex_index] != 0)
                predecessors.push_back(i);
        return predecessors;
    }

    int **_adjacent_matrix;
    int *_indegrees; // used in traverse
    bool *_valid;    // used in traverse

    int _vertex_num;
    int _edge_num;
    int _end_vertex;
};

#endif