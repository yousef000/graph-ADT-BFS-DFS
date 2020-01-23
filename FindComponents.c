#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Graph.h"
#define MAX_LEN 160

int main(int argc, char * argv[]){
    FILE *in, *out;
    int n;                      //number of vertices
    int u, v;                   //first and second vertex respectively
    // check command line for correct number of arguments
    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    // open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if( in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    //==============Allocating, and printing Graph===================
    fscanf(in, "%d", &n);            //scanning number of vertices
    Graph G = newGraph(n);
    
    while (!feof(in)){
        fscanf(in, "%d", &u);       //first vertex
        fscanf(in, "%d", &v);       //second vertex
        if(u == 0 && v ==0)
            break;
        addArc(G,u,v);
    }
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");
    //=================================================================
    List S = newList();
    List SCC = newList();
    for(int i=1; i<=getOrder(G); i++) append(S, i);
    DFS(G, S);
    Graph T = transpose(G);
    DFS(T, S);
    
    int numberOfSCC = 0;
    for(int i = 1; i <= getOrder(G); i++){
        if(getParent(T,i) == NIL)
            numberOfSCC++;
    }
    fprintf(out, "G contains %d strongly connected components:\n", numberOfSCC);
    int k = 1;
    int x;
    for(moveBack(S); index(S)>=0; movePrev(S)){
        x = get(S);
        fprintf(out, "Component %d: ", k);
        while(getParent(T, x) != NIL){
            append(SCC, x);
            movePrev(S);
            x = get(S);
        }
        append(SCC, x);
        for(moveBack(SCC); index(SCC)>=0; movePrev(SCC)){
            int y = get(SCC);
            if(index(SCC) == 0)
                fprintf(out, "%d\n", y);
            else{
                fprintf(out, "%d ", y);
            }
        }
        k++;
        clear(SCC);
    }
    
    
    
    
    freeGraph(&G);
    freeGraph(&T);
    freeList(&S);
    freeList(&SCC);
    fclose(in);
    fclose(out);
    
    
    
    
}

