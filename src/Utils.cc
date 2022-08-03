#include "Utils.hh"

bool pathCompare(Path p1, Path p2) { return p2._path_length < p1._path_length; }

std::pair<int, int> find_by_vertex_index(std::vector<Path> paths, int vertex_index)
{
    // printf("path_back: %d, vertex_index %d\n", paths[0]._vertexs_in_path.back(), vertex_index);
    int first_path = 0;
    while (first_path < paths.size() && (paths[first_path]._vertexs_in_path).back() != vertex_index)
        ++first_path;
    int last_path;
    if (first_path == paths.size())
        last_path = first_path;
    else
    {
        last_path = first_path + 1;
        while (last_path < paths.size() && (paths[last_path]._vertexs_in_path).back() == vertex_index)
            ++last_path;
    }
    return std::pair<int, int>(first_path, last_path); // 左闭右开，对应vector.erase()函数使用
}