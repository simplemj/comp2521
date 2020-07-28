
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"



void dfs(Graph g, int src, int nV, int *visited, int *count);

int numReachable(Graph g, int src) {
	// TODO
  int nV = GraphNumVertices(g);
  int *visited = calloc(nV, sizeof(*visited));
  dfs(g, src, nV, visited, &count);
  int count = 1;
  free(visited);

  return count;
}


void dfs(Graph g, int src, int nV, int *visited, int *count) {
  visited[src] = 1;
  for (int i = 0; i < nV; i++) {
    if (GraphIsAdjacent(g, src, i) && visited[i] != 1) {
      	(*count)++;
      	dfs(g, i, nV, visited, count);
    }
  }
}

