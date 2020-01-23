#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

typedef struct GraphObj{
    int order, size, source;
    List * L;
    int * color;
    int * parent;
    int * distance;
    int * discover;
    int * finish;
} GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    if(G){
        G->L = calloc((n+1), sizeof(List));
        G->color = calloc((n+1), sizeof(int));
        G->parent = calloc((n+1), sizeof(int));
        G->distance = calloc((n+1), sizeof(int));
        G->discover = calloc((n+1), sizeof(int));
        G->finish = calloc((n+1), sizeof(int));
        G->source = NIL;
        G->order = n;
        G->size = 0;
        if(G->L && G->color && G->parent && G->distance){
            for(int i = 1; i <= n; i++){
                G->L[i] = newList();
                G->discover[i] = UNDEF;
                G->finish[i] = UNDEF;
            }
        }
    }
    
    
    return G;
    
}
void freeGraph(Graph* pG){
    if(pG != NULL && *pG != NULL){
        for(int i = 1; i <= getOrder(*pG); i++)
            freeList(&(*pG)->L[i]);
        
        free((*pG)->L);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);
        free((*pG)->discover);
        free((*pG)->finish);
        
        
    }
    free(*pG);
    *pG = NULL;
}
/*** Access functions ***/

int getOrder(Graph G){
    return G->order;
}
int getSize(Graph G){
    return G->size;
}
int getSource(Graph G){
    return G->source;
}
//precondition 1 <= u <= getOrder(G)
int getParent(Graph G, int u){
    if(u < 1 || u > getOrder(G)){
        printf("Error: getParent() called on invalid vertex");
        return 0;
    }
    else if(G->parent[u] == NIL)
        return NIL;
    else{
        return G->parent[u];
    }
}
//precondition 1 <= u <= getOrder(G)
int getDist(Graph G, int u){
    if(u < 1 || u > getOrder(G)){
        printf("Error: getDist() called on invalid vertex");
        return 0;
    }
    else if(G->source == NIL)
        return INF;
    else{
        return G->distance[u];
    }
}
/* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u){
    if(u < 1 || u > getOrder(G)){
        printf("Error: getDiscover() called on invalid vertex");
        return 0;
    }
    else{
        return G->discover[u];
    }
}
/* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u){
    if(u < 1 || u > getOrder(G)){
        printf("Error: getFinish() called on invalid vertex");
        return 0;
    }
    else{
        return G->finish[u];
    }
}
//precondition 1 <= u <= getOrder(G)
//getSource(G)!=NIL
void getPath(List L, Graph G, int u){
    if(u < 1 || u > getOrder(G)){
        printf("Error: getPath() called on invalid vertex");
        return;
    }
    if(getSource(G) == NIL){
        printf("Error: getPath() called on NIL source, BFS() must be called before getPath()");
        return;
    }
    //if reached to the source
    else if(G->parent[u] == getSource(G)){
        prepend(L, u);
        prepend(L, getSource(G));
        
    }
    else if(u == getSource(G))
        append(L,u);
    //if there's no path to source from vertex u
    else if(G->parent[u] == NIL){
        //do nothing, since u doesnt have any adjacent vertex
        //Note this statement will only be true on first recursion
        //since if first u have parent, then there is a path from source
        //to that u.
        prepend(L, NIL);
    }
    //still getting the path
    else{
        prepend(L, u);
        getPath(L, G, G->parent[u]);
    }
    
    
}
/*** Manipulation procedures ***/
void makeNull(Graph G){
    for(int i = 1; i <= G->order; i++)
    {
        clear(G->L[i]);
    }
    G->size = 0;
}
//int arguments must lie in the range 1 to getOrder(G)
void addEdge(Graph G, int u, int v){
    if(u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G)){
        printf("Error: addEdge() called on invalid vertex");
        return;
    }
    else{
        insertSorted(G->L[u], v);
        insertSorted(G->L[v], u);
        G->size++;
    }
   
}
void addArc(Graph G, int u, int v){
    if(u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G)){
        printf("Error: addArc() called on invalid vertex");
        return;
    }
    else{
        insertSorted(G->L[u], v);
        G->size++;
    }
}
//addEdge() and addArc() helper function
void insertSorted(List L, int v){
    if(length(L) == 0){
        append(L, v);
    }
    else{
        //u is added to adjacency list of v
        moveFront(L);
        int k = 1;
        while(k > 0){
            //if reached end of the list, and vertex is not inserted then append
            if(index(L) < 0){
                append(L, v);
                break;
            }
            //insertSorted
            if(v <= get(L)){
                insertBefore(L, v);
                break;
            }
            moveNext(L);
        }
    }
}

void BFS(Graph G, int s){
    for(int i = 1; i <= getOrder(G); i++){
        G->color[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
      
    }
    
    G->source = s;
    G->color[s] = GREY;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List Q = newList();
    append(Q, s);
    
    while (!isEmpty(Q)){
        int u = front(Q);
        deleteFront(Q);
        for(moveFront(G->L[u]); index(G->L[u]) >= 0; moveNext(G->L[u])){
            int v = get(G->L[u]);
            if(G->color[v] == WHITE){
                G->color[v] = GREY;
                G->distance[v] = G->distance[u] + 1;
                G->parent[v] = u;
                append(Q, v);
            }
        }
        G->color[u] = BLACK;
    }
    freeList(&Q);
}
static void Visit(Graph G, int x, int * time){
    G->color[x] = GREY;
    G->discover[x] = ++(*time);
    for(moveFront(G->L[x]); index(G->L[x]) >= 0; moveNext(G->L[x])){
        int y = get(G->L[x]);
        if(G->color[y] == WHITE){
            G->parent[y] = x;
            Visit(G,y,time);
        }
    }
    G->color[x] = BLACK;
    G->finish[x] = ++(*time);
}
void DFS(Graph G, List S){
    if(length(S) != getOrder(G)){
        printf("Error: DFS called on length of List S and order of Graph G that are not equal");
        return;
    }
    int time = 0;
    for(int i = 1; i <= getOrder(G); i++){
        G->color[i] = WHITE;
        G->parent[i] = NIL;
    }
    for(moveFront(S); index(S) >= 0; moveNext(S)){
        int i = get(S);
        if(G->color[i] == WHITE){
            Visit(G, i, &time);
        }
    }
    
    //storing the vertices in order of decreasing finish times in S
    //after DFS is finished
    List L = copyList(S);
    clear(S);
    for(moveFront(L); index(L) >= 0; moveNext(L)){
        int v = get(L);
        if(length(S) == 0){
            append(S, v);
        }
        else{
            int inserted = 0;
            for(moveFront(S); index(S) >= 0; moveNext(S)){
                int w = get(S);
                if(G->finish[v] > G->finish[w]){
                    insertBefore(S, v);
                    inserted = 1;
                    break;
                }
            }
            if(inserted == 0){
                append(S, v);
            }
            
        }
    }
    freeList(&L);
 
}
/* Other Functions */
Graph transpose(Graph G){
    Graph H = newGraph(getOrder(G));
    for(int i = 1; i <= getOrder(G); i++){
        if(length(G->L[i]) > 0){
            for(moveFront(G->L[i]); index(G->L[i]) >= 0; moveNext(G->L[i])){
                int x = get(G->L[i]);
                addArc(H, x, i);
            }
        }
        
    }
    return H;
}
Graph copyGraph(Graph G){
    Graph H = newGraph(getOrder(G));
    for(int i = 1; i <= getOrder(G); i++){
        H->L[i] = copyList(G->L[i]);
        H->color[i] = G->color[i];
        H->parent[i] = G->parent[i];
        H->distance[i] = G->distance[i];
        H->discover[i] = G->discover[i];
        H->finish[i] = G->finish[i];
        H->order= G->order;
        H->size = G->size;
    }
    return H;
}
void printGraph(FILE* out, Graph G){
    int i = 1;
    while(i <= getOrder(G)){
        fprintf(out, "%d: ", i);
        printList(out, G->L[i]);
        fprintf(out, "\n");
        i++;
    }
}

