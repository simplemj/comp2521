
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int shortestDistance(Graph g, int src, int dest) {
	// TODO
	int num = GraphNumVertices(g);
	int *dist = calloc(num,sizeof(*dist));
	Queue new = QueueNew();
	QueueEnqueue(new,src);
	while(!QueueIsEmpty(new)) {
		int v = QueueDequeue(new);
		for(int w = 0; w < num; w++) {
			if((dist[w] == 0 || dist[w] + 1 < dist[v]) && GraphIsAdjacent(g, v, w) && w != src) {
				dist[w] = dist[v] + 1;
				QueueEnqueue(new,w);
			}
		}
	}

	for(int i = 0; i < num; i++) {
		if(dist[i] == 0 && i != src) {
			dist[i] = -1;
		}
	}
	int ans = dist[dest];
	return ans;
}

