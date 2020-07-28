// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// Helper functions
static NodeValues newNV(Graph g);
static double countST(ShortestPaths sp, Vertex s, Vertex d);
static double countSTV(ShortestPaths sp, Vertex v, Vertex s, Vertex d);

// Find the outdegree centrality of whole graph
NodeValues outDegreeCentrality(Graph g){
    assert(g != NULL);
    // initialize nodevalues
    NodeValues nv = newNV(g);
    int num = numVerticies(g);
    // loop whole graph 
    // and count the length of outIncident list for each vertex
    for (int i = 0; i < num; i++) {
        int count = 0;
        for (AdjList tmp = outIncident(g, i); tmp != NULL; tmp = tmp->next) {
            count++;
        }
        nv.values[i] = count;
    }
	return nv;
}

// Find the indegree centrality of whole graph
NodeValues inDegreeCentrality(Graph g){
    assert(g != NULL);
    // initialize nodevalues
    NodeValues nv = newNV(g);
    int num = numVerticies(g);
    // loop whole graph 
    // and count the length of intIncident list for each vertex
    for (int i = 0; i < num; i++) {
        int count = 0;
        for (AdjList tmp = inIncident(g, i); tmp != NULL; tmp = tmp->next) {
            count++;
        }
        nv.values[i] = count;
    }
	return nv;
}

// Find the degree centrality of whole graph
NodeValues degreeCentrality(Graph g) {
    assert(g != NULL);
    // initialize nodevalues
    NodeValues nv = newNV(g);
    int num = numVerticies(g);
    // loop whole graph 
    // and count the  sum of length of 
    // outIncident list and outIncident list for each vertex
    for (int i = 0; i < num; i++) {
        double count = 0;
        for (AdjList tmp = outIncident(g, i); tmp != NULL; tmp = tmp->next) {
            count++;
        }
        for (AdjList tmp = inIncident(g, i); tmp != NULL; tmp = tmp->next) {
            count++;
        }
        nv.values[i] = count;
    }
    return nv;
}

// Find the closeness centrality of whole graph
NodeValues closenessCentrality(Graph g){
    assert(g != NULL);
    // initialize nodevalues
    NodeValues nv = newNV(g);
    int num = numVerticies(g);
    // loop whole graph
    // count the total shortest paths for each vertex
    // and mark vertex which have no shortest and not sorce as isolated node
    // then use formula to calculate closeness centrality for each vertex
    for (int i = 0; i < num; i++) {
        ShortestPaths sp = dijkstra(g, i);
        double td = 0;
        int in = 0;
        for (int j = 0; j < num; j++) {
            td = td + sp.dist[j];
            if (j != i && sp.dist[j] == 0)
                in = in + 1;
        }
        double n = num - in;
        double N = num;
        double cc = 0;
        // make sure denominator not equal to zero
        if ((N - 1) != 0 && td != 0)
            cc = ((n - 1) / (N - 1)) * ((n - 1) / td);
        nv.values[i] = cc;
    }
	return nv;
}

// Find the betweenness centrality of whole graph
NodeValues betweennessCentrality(Graph g){
    assert(g != NULL);
    // initialize nodevalues
    NodeValues nv = newNV(g);
    int num = numVerticies(g);
    // loop whole graph
    // use helper funtions to find total shortest paths
    // and total shortest paths pass though vertex v
    // then use formula to calculate betweenness centrality for each vertex
    for (int v = 0; v < num; v++) {
        double bc = 0;
        // loop for sorce
        for (int s = 0; s < num; s++) {
            // loop for destination
            for (int d = 0; d < num; d++) {
                ShortestPaths sp = dijkstra(g, s);
                if (s != v && d != v) {
                    double st = 0;
                    st = countST(sp, s, d);
                    double stv = 0;                   
                    stv = countSTV(sp, v, s, d);
                    // make sure denominator not equal to zero
                    if (st != 0)
                        bc = bc + (stv / st);
                }
            }
        }
        nv.values[v] = bc;
    }
	return nv;
}

// Find the normalised betweenness centrality of whole graph
NodeValues betweennessCentralityNormalised(Graph g){
    assert(g != NULL);
    NodeValues nv = newNV(g);
    int num = numVerticies(g);
    assert(num > 2);
    // loop whole graph
    // use helper funtions to find total shortest paths
    // and total shortest paths pass though vertex v
    // then use formula to calculate normalised betweenness centrality for each vertex
    for (int v = 0; v < num; v++) {
        double bc = 0;
        for (int s = 0; s < num; s++) {
            for (int d = 0; d < num; d++) {
                ShortestPaths sp = dijkstra(g, s);
                if (s != v && d != v) {
                    double st = 0;
                    st = countST(sp, s, d);
                    double stv = 0;                   
                    stv = countSTV(sp, v, s, d);
                    // make sure denominator not equal to zero
                    if (st != 0)
                        bc = bc + (stv / st);
                }
            }
        }
        double bcn = 0;
        // make sure denominator not equal to zero
        if ((num - 1) != 0 && (num - 2) != 0) 
            bcn = bc / ((num - 1) * (num - 2));
        nv.values[v] = bcn;
    }
	return nv;
}

// Print NodeValues
void showNodeValues(NodeValues values){
    for (int i = 0; i < values.noNodes; i++) { 
        printf("%d: %f\n", i, values.values[i]);
    }
}

// Free NodeValues
void freeNodeValues(NodeValues values){
    free(values.values);
}

// Helper functions for creat a new NodeValues
static NodeValues newNV(Graph g) {
    assert(g != NULL);
    int num = numVerticies(g);
    NodeValues nv;
    nv.noNodes = num;
    nv.values = malloc(num * sizeof(double));
	return nv;
}

// Helper functions for calculate the number of shortest paths
// from sorce vertex to destination vertex by using recursion
static double countST(ShortestPaths sp, Vertex s, Vertex d) {
    double st = 0;
    PredNode *pn = sp.pred[d];
    if (s == d)
        return 1;
    while (pn != NULL) {
        st = st + countST(sp, s, pn->v);
        pn = pn->next;
    }
    return st;
}

// Helper functions for calculate the number of shortest paths
// from sorce vertex to destination vertex which pass through given vertex v
// by using recursion
static double countSTV(ShortestPaths sp, Vertex v, Vertex s, Vertex d) {
    double stv = 0;
    PredNode *pn = sp.pred[d];
    if (s == d) {
        return 0;
    } else if (s == v || d == v) {
        return countST(sp, s, d);
    }
    while (pn != NULL) {
        stv = stv + countSTV(sp, v, s, pn->v);
        pn = pn->next;
    }
    return stv;
}
