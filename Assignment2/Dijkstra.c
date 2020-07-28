// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

// Helper functions
static ShortestPaths newSP(Graph g, Vertex v);
static ItemPQ newIPQ(int key, int value);
static PredNode* newNode(int v);
static PredNode* addNode(PredNode *pn, int v);
static void freeNode(PredNode *pn);

// Finds shortest paths from a given vertex to all other vertices
ShortestPaths dijkstra(Graph g, Vertex v) {
    assert(g != NULL);
	ShortestPaths sp = newSP(g, v);
	int num = numVerticies(g);
	// initialize the shortestpaths 
	// and predecesor list
	for (int i = 0; i < num; i++) {
	    sp.dist[i] = 0;
	    sp.pred[i] = NULL;
	}
	// initialize a priority queue for graph
	ItemPQ ipq = newIPQ(v, 0);
	PQ pq = newPQ();
	addPQ(pq, ipq);
	while (PQEmpty(pq) == 0) {
	    ItemPQ tmp = dequeuePQ(pq);
	    // loop this vertex
	    for (AdjList l = outIncident(g, tmp.key); l != NULL; l = l->next) {
	        // if it's not visited yet
	        // update the shortest path and predecesor list
	        // then add it to the priority queue
	        if (sp.dist[l->w] == 0 && l->w != v) { 
	            sp.dist[l->w] = sp.dist[tmp.key] + l->weight;
	            sp.pred[l->w] = addNode(sp.pred[l->w], tmp.key);
	            ipq = newIPQ(l->w, sp.dist[l->w]);
	            addPQ(pq, ipq);
	        // if it's visited
	        // check if need to updated shortest path and predecesor list
	        // and do not add to priority queue again
	        } else {
	            // if new path shorter
	            // update the shortest path and predecesor list
	            // then update the priority queue
	            if ((sp.dist[tmp.key] + l->weight) < sp.dist[l->w]) {
	                sp.dist[l->w] = sp.dist[tmp.key] + l->weight;
	                freeNode(sp.pred[l->w]);
	                sp.pred[l->w] = NULL;
	                sp.pred[l->w] = addNode(sp.pred[l->w], tmp.key);
	                ipq = newIPQ(l->w, sp.dist[l->w]);
	                updatePQ(pq, ipq);
	            // if new path is same with old one 
	            // update the predecesor list
	            } else if (sp.dist[l->w] == (sp.dist[tmp.key] + l->weight)) {
	                sp.pred[l->w] = addNode(sp.pred[l->w], tmp.key);
	            }
	        }
	    }
	}
	freePQ(pq);
	return sp;
}

// Print the whole shortestpaths
void showShortestPaths(ShortestPaths paths) {
    printf("Node %d\n", paths.src);
    // print the shortest path
    printf(" Distance\n");
    for (int i = 0; i < paths.noNodes; i++) {
        if(i == paths.src)
            printf("   %d : X\n", i);
        else
            printf("   %d : %d\n", i, paths.dist[i]);
    }
    // print the predecesor list
    printf("  Preds\n");
	for (int i = 0; i < paths.noNodes; i++) {
		printf("   %d : ", i);
		PredNode *tmp = paths.pred[i];
		while (tmp != NULL) {
			printf("[%d]->", tmp->v);
			tmp = tmp->next;
		}
		printf("NULL\n");
	}
}

// Free whole ShortestPaths
void  freeShortestPaths(ShortestPaths paths) {
    // free shortest paths
    free(paths.dist);
    // free predecesor list
	for (int i = 0; i < paths.noNodes; i++) {
		freeNode(paths.pred[i]);
	}
	free(paths.pred);
}

// Helper function for creat new ShortestPaths
// by given graph and vertex
static ShortestPaths newSP(Graph g, Vertex v) {
    assert(g != NULL);
    int num = numVerticies(g);
    ShortestPaths new;
    new.noNodes = num;
    new.src = v;
    new.dist = malloc(num * sizeof(int));
    new.pred = malloc(num * sizeof(PredNode*));
    return new;
}

// Helper function for creat new ItemPQ
// by given key and value
static ItemPQ newIPQ(int key, int value) {
    ItemPQ new;
    new.key = key;
    new.value = value;
    return new;
}

// Helper function for creat new PredNode*
// by given value
static PredNode* newNode(int v) {
    PredNode *new = malloc(sizeof(PredNode));
    new->v = v;
    new->next = NULL;
    return new;
}

// Helper function for add new PredNode*
// to the end of PredNode list
static PredNode* addNode(PredNode *pn, int v) {
    PredNode *new = newNode(v);
    if (pn == NULL)
        return new;
    for (PredNode *tmp = pn; tmp != NULL; tmp = tmp->next) {
        if (tmp->next == NULL) {
            tmp->next = new;
            break;
        }
    }
    return pn;
}

// helper fuction for free whole PredNode* list
static void freeNode(PredNode *pn) {
    if (pn == NULL) 
        return;
    PredNode *tmp = pn;
    while (tmp != NULL) {
        PredNode *ttmp = tmp;
        tmp = tmp->next;
        ttmp->next = NULL;
        free(ttmp);
    }
}
