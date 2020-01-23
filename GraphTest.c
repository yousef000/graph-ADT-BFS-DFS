//-----------------------------------------------------------------------------
// GraphClient.c
// Test client for the Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
    int i, n=8;
    List S = newList();
    Graph G = newGraph(n);
    Graph T=NULL, C=NULL;
    
    for(i=1; i<=n; i++) append(S, i);
    
    
    addArc(G, 1,2);
    addArc(G, 2,3);
    addArc(G, 2,5);
    addArc(G, 2,6);
    addArc(G, 3,4);
    addArc(G, 3,7);
    addArc(G, 4,3);
    addArc(G, 4,8);
    addArc(G, 5,1);
    addArc(G, 5,6);
    addArc(G, 6,7);
    addArc(G, 7,6);
    addArc(G, 7,8);
    addArc(G, 8,8);
    printGraph(stdout, G);
    
    DFS(G, S);
    printList(stdout, S);
    T = transpose(G);
    printGraph(stdout, T);
    printList(stdout, S);
    DFS(T, S);
    printList(stdout, S);
    
    fprintf(stdout, "\n");
    fprintf(stdout, "x:  d  f  p\n");
    for(i=1; i<=n; i++){
        fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
    }

    
    
    int numberOfSCC = 0;
    for(int i = 1; i <= getOrder(T); i++){
        if(getParent(T,i) == NIL)
            numberOfSCC++;
    }
    List SCC = newList();
    printf("G contains %d strongly connected components:\n", numberOfSCC);
    int k = 1;
    int x;
    for(moveBack(S); index(S)>=0; movePrev(S)){
        x = get(S);
        fprintf(stdout, "Component %d: ", k);
        while(getParent(T, x) != NIL){
            append(SCC, x);
            movePrev(S);
            x = get(S);
        }
        append(SCC, x);
        for(moveBack(SCC); index(SCC)>=0; movePrev(SCC)){
            int y = get(SCC);
            if(index(SCC) == 0)
                fprintf(stdout, "%d\n", y);
            else{
                fprintf(stdout, "%d ", y);
            }
        }
        k++;
        clear(SCC);
    }
    
    fprintf(stdout, "\n");
    fprintf(stdout, "x:  d  f  p\n");
    for(i=1; i<=n; i++){
        fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
    }
    fprintf(stdout, "\n");
    printList(stdout, S);
    fprintf(stdout, "\n");

    T = transpose(G);
    C = copyGraph(G);
    fprintf(stdout, "\n");
    printGraph(stdout, C);
    fprintf(stdout, "\n");
    printGraph(stdout, T);
    fprintf(stdout, "\n");
    
    DFS(T, S);
    fprintf(stdout, "\n");
    fprintf(stdout, "x:  d  f  p\n");
    for(i=1; i<=n; i++){
        fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
    }
    fprintf(stdout, "\n");
    printList(stdout, S);
    fprintf(stdout, "\n");
    
    freeList(&S);
    freeGraph(&G);
    freeGraph(&T);
    freeGraph(&C);
    return(0);
}


