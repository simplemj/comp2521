// Graph ADT interface for Ass2 (COMP2521)
#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

// Define the Grapsh structure by using Adjacency list
struct GraphRep{
    int nV;
    int nE;
    AdjList *AList;
};

// Helper functions
static bool checkV(AdjList l, Vertex v);
static AdjList newNode(Vertex v, int weight);
static AdjList insertNode(AdjList l, Vertex v, int weight);
static AdjList removeNode(AdjList l, Vertex v);
static void freeList(AdjList l);

// Creat a new graph
Graph newGraph(int noNodes) {
    // check given noNodes is valid
    assert(noNodes >= 0);
    Graph new = malloc(sizeof(struct GraphRep));
    // check allocating valid meory for graph
    assert(new != NULL);
    // initialize the number of vertices and edges
    new->nV = noNodes;
    new->nE = 0;
    new->AList = malloc(noNodes * sizeof(AdjList));
    // check allocating valid meory for Adjacency list
    assert(new->AList != NULL);
    // initialize Adjacency list
    for (int i = 0; i < noNodes; i++) {
        new->AList[i] = NULL;
    }
	return new;
}

// Find number of verticies in graph
int numVerticies(Graph g) {
    assert(g != NULL);
	return g->nV;
}

// Insert the new edge to graph
void  insertEdge(Graph g, Vertex src, Vertex dest, int weight) {
	assert(g != NULL);
	// check if this edge is not in the given graph
	// then add the edge and update edges' number
	if (checkV(g->AList[src], dest) == 0) {
	    g->AList[src] = insertNode(g->AList[src], dest, weight);
	    g->nE++;
	}
}

// Remove the edge from graph
void  removeEdge(Graph g, Vertex src, Vertex dest) {
    assert(g != NULL);
    // check if this edge is in the given graph
	// then remove the edge and update edges' number
    if (checkV(g->AList[src], dest) == 1) {
        g->AList[src] = removeNode(g->AList[src], dest);
        g->nE--;
    }
}

// Check if a edge in the graph
bool adjacent(Graph g, Vertex src, Vertex dest) {
    assert(g != NULL);
    // if the edge in the graph
    // then return true
    if (checkV(g->AList[src], dest) == 1) {
        return 1;
    }
	return 0;
}

// Returns a list of adjacent vertices 
// on outgoing edges from a given vertex
AdjList outIncident(Graph g, Vertex v) {
    assert(g != NULL);
    // return the adjacent list of given graph
    // for given vertex
	return g->AList[v];
}

// Returns a list of adjacent vertices
// on incoming edges from a given vertex
AdjList inIncident(Graph g, Vertex v) {
    assert(g != NULL);
    // initialize a new Adjacency list
	AdjList l = malloc(sizeof(adjListNode));
	AdjList tmp = l;
	tmp->next = NULL;
	// go through whole graph
	for (int i = 0; i < g->nV; i++) {
	    // if the edge in the graph
	    // and the vertex is not itself 
	    // storge data in the new list
		if (checkV(g->AList[i], v) == 1 && i != v) {
			if (tmp->next != NULL) 
			    tmp = tmp->next;
			tmp->w = i;
			tmp->weight = g->AList[i]->weight;
			tmp->next = malloc(sizeof(adjListNode));
		}
	}
	// if there's no incoming edge 
	// then return null
	if (tmp->next == NULL) {
		free(tmp);
		l = NULL;
	} else {
		free(tmp->next);
		tmp->next = NULL;
	}
	return l;
}

// Print the whole graph
void  showGraph(Graph g) {
    assert (g != NULL);
    // print the numbers of vertices and edges
    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    // loop the whole graph and print the pathes with weight
    for (int i = 0; i < g->nV; i++) {
        printf("Vertex %d\n", i);
        for (AdjList n = g->AList[i]; n != NULL; n = n->next) {
            printf("%d (weight: %d) ->", n->w, n->weight);
        }
        printf("\n");
    }
}

// Free the whole graph
void  freeGraph(Graph g) {
    // loop the whole graph and free the Adjaceny lists for each vertex
    for (int i = 0; i < g->nV; i++) {
        freeList(g->AList[i]);
    }
    // free the graph
    free(g);
}

// Helper function for checking 
// if a given vertex in the given Adjaceny list
static bool checkV(AdjList l, Vertex v) { 
    for (AdjList tmp = l; tmp != NULL; tmp = tmp->next) {
        if (tmp->w == v)
            return 1;
    }
    return 0;
}

// Helper function for creat a new AdjNode* 
// by given Vertex and weight
static AdjList newNode(Vertex v, int weight) {
    AdjList new = malloc(sizeof(adjListNode));
    new->w = v;
    new->weight = weight;
    new->next = NULL;
    return new;
}

// Helper function for insert a new AdjNode*
// to the front of given list
static AdjList insertNode(AdjList l, Vertex v, int weight) {
    AdjList new = newNode(v, weight);
    new->next = l;
    return new;
}

// Helper function for remove a AdjNode* from AdjList
// by given vertex
static AdjList removeNode(AdjList l, Vertex v) {
    if (l == NULL) 
        return l;
    AdjList tmp = l;
    if (tmp->w == v) {
        return tmp->next;
    } else {
        while (tmp != NULL) {
            AdjList curr = tmp;
            tmp = tmp->next;
            if (tmp->w == v) {
                tmp = tmp->next;
                curr->next = tmp;
                break;
            }
        }
    }
    return l;
}

// Helper function for free the whole Adjacency list
static void freeList(AdjList l) {
    AdjList tmp = l;
    while (tmp != NULL) {
        AdjList ttmp = tmp;
        tmp = tmp->next;
        ttmp->next = NULL;
        free(ttmp);
    }
}
