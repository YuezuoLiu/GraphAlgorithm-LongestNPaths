#include "Graph.hh"

#include <cstdio>

Graph::~Graph()
{
    if (_adjacent_matrix != nullptr)
    {
        for (int i = 0; i < _edge_num; ++i) // delete adjacent matrix
        {
            delete[] _adjacent_matrix[i];
        }
        delete[] _adjacent_matrix;
    }
    if (_indegrees != nullptr)
        delete[] _indegrees;
    if (_valid != nullptr)
        delete[] _valid;
}

void Graph::makeGraph()
{
    printf("Enter vertex number and edge number, format: vertex_num edge_num: ");
    scanf("%d %d", &_vertex_num, &_edge_num);
    _adjacent_matrix = new int *[_vertex_num]; // allocate adjacent matrix and initiate in_degree array and valid array;
    for (int i = 0; i < _vertex_num; ++i)
        _adjacent_matrix[i] = new int[_vertex_num];

    int out_vertex, in_vertex, weight;
    for (int i = 0; i < _edge_num; ++i) // input edges to adjacent matrix
    {
        printf("Enter %d th edge, format: out_vertex in_vertex weight:", i);
        scanf("%d %d %d", &out_vertex, &in_vertex, &weight);
        _adjacent_matrix[out_vertex][in_vertex] = weight;
    }
    printf("Graph constructed. vertex number: %d, edge number: %d\n", _vertex_num, _edge_num);
}

void Graph::initiateTraverseData() //初始化遍历需要的数据
{
    _indegrees = new int[_vertex_num]; // allocate in_degree array
    _valid = new bool[_vertex_num];
    for (int i = 0; i < _vertex_num; ++i)
    {
        _indegrees[i] = 0;
        _valid[i] = true;
    }

    int outdegree;
    for (int i = 0; i < _vertex_num; ++i) // 初始化indegree数组，同时计算出度为0结点
    {
        outdegree = 0;
        for (int j = 0; j < _vertex_num; ++j)
        {
            if (_adjacent_matrix[i][j] != 0)
                ++_indegrees[j];
            if (_adjacent_matrix[i][j] != 0)
                ++outdegree;
        }
        if (outdegree == 0)
            _end_vertex = i; // 计算结束节点
    }
    printf("end_vertex: %d\n", _end_vertex);

    printf("indegree array: ");
    for (int i = 0; i < _vertex_num; ++i)
        printf("%d ", _indegrees[i]);
    printf("\n");
}

void Graph::traverse(int n)
{
    initiateTraverseData();
    std::vector<Path> paths;

    for (int i = 0; i < _vertex_num; ++i) // eliminate one vertex from graph once;
    {
        printf("\nround %d: ", i);
        showIndegree();

        int zero_indegree_vertex_index = findZeroIndegreeVertex(); //找到一个入度为0的节点
        // printf("zero_indegree_vertex_index: %d\n", zero_indegree_vertex_index);
        if (zero_indegree_vertex_index == -1)
        {
            printf("error\n");
            return;
        }

        if (paths.size() == 0) // first path;
        {
            Path new_path;
            new_path._vertexs_in_path.push_back(zero_indegree_vertex_index);
            paths.push_back(new_path);

            printf("new_path: ");
            new_path.show();
        }

        else // not first path
        {
            // printf("successor num: %d\n", getSuccessors(zero_indegree_vertex_index).size());
            for (int predecessor : getPredecessors(zero_indegree_vertex_index)) //当前要消去节点所有前驱节点
            {
                std::pair<int, int> paths_ended_with_current_vertex = find_by_vertex_index(paths, predecessor); //以上一个结束的所有path

                int i = paths_ended_with_current_vertex.first;
                int j = paths_ended_with_current_vertex.second;
                // printf("first: %d, last: %d\n", i, j);
                while (i != j)
                {
                    Path new_path = paths[i];                                                           // 复制旧路径
                    new_path._vertexs_in_path.push_back(zero_indegree_vertex_index);                    // 路径中添加当前节点
                    new_path._path_length += _adjacent_matrix[predecessor][zero_indegree_vertex_index]; // 增加路径长度
                    paths.push_back(new_path);                                                          // 保存新路径
                    ++i;

                    printf("new path: ");
                    new_path.show();
                }
            }
        }
        updateIndegreeArray(zero_indegree_vertex_index); // update indegree array
        _valid[zero_indegree_vertex_index] = false;
        // printf("round %d , path_num: %d\n", i, paths.size());
    }

    printf("\ntotal path number: %d\n", paths.size());
    sort(paths.begin(), paths.end(), pathCompare);

    printf("\nlongest %d paths: \n", n);
    int path_founded = 0;
    for (int i = 0; i < paths.size() && path_founded < n; ++i)
        if (paths[i]._vertexs_in_path.back() == _end_vertex) // 只需要到达终点的路径
        {
            paths[i].show();
            ++path_founded;
        }
}