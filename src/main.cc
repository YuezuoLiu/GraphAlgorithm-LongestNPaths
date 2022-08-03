#include "Graph.hh"

#define LONGEST_N_PATH 3
int main()
{
    Graph g;

    g.makeGraph();
    g.showMatrix();

    g.traverse(LONGEST_N_PATH);
    return 0;
}