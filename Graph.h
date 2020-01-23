#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include<stdio.h>
#include "List.h"
#define NIL 0
#define INF -1
#define UNDEF -2
#define WHITE 0
#define GREY 1
#define BLACK 2
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
void DFS(Graph G, List S);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);
void insertSorted(List L, int v);
/* Other Functions */
Graph transpose(Graph G);
Graph copyGraph(Graph G);



#endif


