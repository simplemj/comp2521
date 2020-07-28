
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"


void dfscheck(Graph g,int src,int *visited);

void depthFirstSearch(Graph g, int src) {
	// TODO
	int num = GraphNumVertices(g);
	int *visited = calloc(num, sizeof(*visited));
	for(int i = 0; i < num; i++) visited[i] = -1;
	visited[src] = src;
	printf("%d ",src);
	dfscheck(g,src,visited);
}

void dfscheck(Graph g,int src,int *visited) {
	int num = GraphNumVertices(g);
	for(int w = 0;w < num; w++) {
		if(GraphIsAdjacent(g,src,w) == true) {	
			if(visited[w] == -1){
				visited[w] = w;
				printf("%d ",w);
				dfscheck(g,w,visited);
			}
		}
	}
}