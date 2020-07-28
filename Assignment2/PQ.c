// PQ ADT interface for Ass2 (COMP2521)
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define HEAPSIZE 10000

// Define the Priority Queue by using heap
struct PQRep {
    ItemPQ *heap;
    int nitems;
};

// Helper functions
static void swap(ItemPQ *ipq, int i, int j);
static void fixUp(ItemPQ *ipq, int i);
static void fixDown(ItemPQ *ipq, int i, int N);

// Creat a new priority queue
PQ newPQ() {
    PQ new = malloc(sizeof(struct PQRep));
    // check allocating valid meory for priority queue
    assert(new != NULL);    
    new->heap = malloc(HEAPSIZE * sizeof(ItemPQ));
    // check allocating valid meory for heap
    assert(new->heap != NULL);
    // initialize the number of nitems
    new->nitems = 0;
    return new;
}

// Check if the priority queue is empty
int PQEmpty(PQ p) {
    assert(p != NULL);
    // if there's no items in priority queue
    // then return true
    if (p->nitems == 0)
        return 1;
    return 0;
}

// Add new element to given priority queue
// if the element with 'key' exists
// it's 'value' is updated
// reference code from lecture
void addPQ(PQ pq, ItemPQ element) {
    assert(pq != NULL);
    pq->nitems++;
    // add element to the heap
    pq->heap[pq->nitems] = element;
    // fix heap to correct position
    fixUp(pq->heap, pq->nitems);
}

// Removes and returns the element from priority queue 
// with smallest 'value'
// reference code from lecture
ItemPQ dequeuePQ(PQ pq) {
    assert(pq != NULL);
    // if PQ is empty 
    // then return a 'empty' element
    if (PQEmpty(pq) == 1) {
        ItemPQ ipq;
        ipq.value = -1;
        ipq.key = -1;
        return ipq;
    }
    // remove and return the root of heap
    ItemPQ tmp = pq->heap[1];
	pq->heap[1] = pq->heap[pq->nitems];
	pq->nitems--;
	fixDown(pq->heap, 1, pq->nitems);	
	return tmp;
}

// Updates element with a given 'key' value
// by updating that item's value to the given 'value'
// if element with 'key' does not exist in the queue
// then no action is taken
void updatePQ(PQ pq, ItemPQ element) {
    assert(pq != NULL);
    // loop the priority queue to find the target 'key'
    int target = -1;
    for (int i = 1; i <= (pq->nitems); i++){
		if (pq->heap[i].key == element.key) {
		    target = i;
		    break;
		}
	}
	// update the 'value' of target
	int tmp = pq->heap[target].value;
	pq->heap[target].value = element.value;
	// fix heap to correct position
	if (element.value < tmp) {
	    fixUp(pq->heap, target);
	} else if (element.value > tmp) {
	    fixDown(pq->heap, target, pq->nitems);
	}	    
}

// Print the whole priority queue 
void  showPQ(PQ pq) {
    assert(pq != NULL);
    printf("Priority queue: \n");
    // loop priority queue to print 'key' and 'value' of each element
    for (int i = 1; i <= pq->nitems; i++) {
        printf("Index: %d, Value: %d \n", i, pq->heap[i].value);
    }
}

// Free the whole priority queue 
void  freePQ(PQ pq) {
    assert(pq != NULL);
    // free the heap 
    free(pq->heap);
    // free the PQ
	free(pq);
}

// Swap the position of two item in the heap
// reference code from lecture
static void swap(ItemPQ *ipq, int i, int j) {
    ItemPQ tmp = ipq[i];
    ipq[i] = ipq[j];
    ipq[j] = tmp;
}

// Fix up the item postion in the heap
// reference code from lecture
static void fixUp(ItemPQ *ipq, int i) {
    while (i > 1 && (ipq[i].value <= ipq[i / 2].value)) {
        swap(ipq, i, i / 2);
        i = i / 2;
    }
}

// Fix down the item position in the heap
// reference code from lecture
static void fixDown(ItemPQ *ipq, int i, int N) {
    while (2 * i <= N) {
        int j = 2 * i;
        if (j < N && (ipq[j].value > ipq[j + 1].value)) 
            j++;
        if (ipq[i].value < ipq[j].value) 
            break;
        swap(ipq, i, j);
        i = j;
    }
}
