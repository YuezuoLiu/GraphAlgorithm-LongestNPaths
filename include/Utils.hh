#ifndef CPP_PROGRAM_ASSIGNMENT1_INCLUDE_UTILS_HH_
#define CPP_PROGRAM_ASSIGNMENT1_INCLUDE_UTILS_HH_

#include <vector>
#include <algorithm>
//#include "Edge.hh"

class Path
{
public:
    Path() { _path_length = 0; }
    void show()
    {
        printf("( ");
        for (int i = 0; i < _vertexs_in_path.size() - 1; ++i)
            printf("%d --> ", _vertexs_in_path[i]);
        printf("%d )", _vertexs_in_path.back());
        printf(" path_length: %d\n", _path_length);
    }

    int _path_length;
    std::vector<int> _vertexs_in_path;
};

class SimpleVertex
{
public:
    SimpleVertex(int v, int id) { _vertex_index = v, _in_degree = id; }
    int _vertex_index;
    int _in_degree;
};

bool pathCompare(Path p1, Path p2);

std::pair<int, int> find_by_vertex_index(std::vector<Path> paths, int vertex_index);

#endif