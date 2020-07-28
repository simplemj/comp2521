
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"


void breadthFirstSearch(Graph g, int src) {
	int num  = GraphNumVertices(g);
	int *visited = calloc(num,sizeof(*visited));
	for(int i = 0; i < num; i++) visited[i] = -1;
	visited[src] = src;
	printf("%d ",src);
	Queue pq = QueueNew();
	QueueEnqueue(pq,src);
	while(!QueueIsEmpty(pq)) {
		int v = QueueDequeue(pq);
		for(int w = 0;w < num; w++) {
			if(GraphIsAdjacent(g,v,w) == true && visited[w] == -1) {
					visited[w] = w;
					printf("%d ",w);
					QueueEnqueue(pq,w);
			}
			
		}
	}
	free(visited);
	// TODO
}

