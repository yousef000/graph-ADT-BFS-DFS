//-----------------------------------------------------------------------------------------
// List.c
// Yousef Dost
// ydost@ucsc.edu
// PA2
// An integer List ADT
//-----------------------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

typedef struct NodeObj{
    int data;
    struct NodeObj * next;
    struct NodeObj * previous;
} NodeObj;
typedef NodeObj * Node;
typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

//Initiallization
Node newNode(int data){
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->previous = NULL;
    return(N);
}
void freeNode(Node * pN){
    if( pN != NULL && *pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}
List newList(){
    List L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return(L);
    
}
void freeList(List * pL){
    if(pL != NULL && *pL != NULL){
        while(!isEmpty(*pL)){
            deleteBack(*pL);
            
        }
        free(*pL);
        *pL = NULL;
    }
}
// Access functions
void errorPrompt(char str[]){
    printf("List Error: calling %s", str);
    printf(" on NULL List reference\n");
    exit(1);
}
int length(List L){
    return L->length;
}
int index(List L){
    if( L == NULL )
        errorPrompt("index()");
    if(L->cursor == NULL)
        return -1;
    else{
        return L->index;
    }
    
}
int front(List L){
    if( L == NULL )
        errorPrompt("front()");
    if(isEmpty(L)){
        printf("front() called on empty List");
        exit(1);
    }
    else{
        return L->front->data;
    }
}
int back(List L){
    if( L == NULL )
        errorPrompt("back()");
    if(isEmpty(L)){
        printf("back() called on empty List");
        exit(1);
    }
    else{
        return L->back->data;
    }
    
}
int get(List L){
    if( L == NULL )
        errorPrompt("get()");
    if(isEmpty(L)){
        printf("get() called on empty List");
        exit(1);
    }
    else if(L->index < 0){
        printf("get() called on undefined index");
        exit(1);
    }
    else{
        return L->cursor->data;
    }
    
}
int equals(List A, List B){
    if( A == NULL || B == NULL)
        errorPrompt("equals()");
    if(length(A) != length(B))
        return 0;
    else{
        int Equals = 1;
        moveFront(A);
        moveFront(B);
        while(A->cursor != NULL && Equals == 1){
            if(A->cursor->data != B->cursor->data)
                Equals = 0;
            moveNext(A);
            moveNext(B);
            
        }
        return Equals;
    }
}
// Manipulation procedures --------------------------------------------------
void clear(List L){
    L->front = L->back = NULL;
    L->length = 0;
    L->cursor = NULL;
}
int isEmpty(List L){
    if( L == NULL )
        errorPrompt("isEmpty()");
    if(L->length == 0)
        return 1;
    else{
        return 0;
    }
}
void moveFront(List L){
    if( L == NULL)
        errorPrompt("moveFront()");
    if(!isEmpty(L)){
        L->cursor = L->front;
        L->index = 0;
    }
    
}
void moveBack(List L){
    if( L == NULL)
        errorPrompt("moveBack()");
    if(!isEmpty(L)){
        L->cursor = L->back;
        L->index = L->length-1;
    }
}
void movePrev(List L){
    if(L == NULL)
        errorPrompt("movePrev()");
    if(L->cursor != L->front && L->cursor != NULL){
        L->cursor = L->cursor->previous;
        L->index--;
    }
    else if(L->cursor == L->front && L->cursor != NULL)
        L->cursor = NULL;
    else{
        //if cursor is NULL do nothing
    }
}
void moveNext(List L){
    if(L == NULL)
        errorPrompt("moveNext()");
    if(L->cursor != L->back && L->cursor != NULL){
        L->cursor = L->cursor->next;
        L->index++;
    }
    else if(L->cursor == L->back && L->cursor != NULL)
        L->cursor = NULL;
    else{
        //if cursor is NULL do nothing
    }
}
void prepend(List L, int data){
    if(L == NULL)
        errorPrompt("prepend()");
    if(isEmpty(L)){
        Node temp = newNode(data);
        L->front = L->back = temp;
    }
    else{
        Node temp = newNode(data);
        temp->next = L->front;
        L->front->previous = temp;
        L->front = temp;
    }
    L->length++;
    L->index++;
}
void append(List L, int data){
    if(L == NULL)
        errorPrompt("append()");
    if(L->length <= 0){
        Node temp = newNode(data);
        L->front = L->back = temp;
    }
    else{
        Node temp = newNode(data);
        L->back->next = temp;
        temp->previous = L->back;
        L->back = temp;
    }
    L->length++;
}
void insertBefore(List L, int data){
    if(L == NULL)
        errorPrompt("insertBefore()");
    if(isEmpty(L))
        printf("InsertBefore() called on empty List");
    if(L->index < 0)
        printf("InsertBefore() called on undefined index");
    else if(L->cursor->previous == NULL){     //Node = front
        prepend(L, data);
    }
    else{
        Node temp = newNode(data);
        L->cursor->previous->next = temp;
        temp->previous = L->cursor->previous;
        temp->next = L->cursor;
        L->cursor->previous = temp;
        L->index++;
        L->length++;
    }
}
void insertAfter(List L, int data){
    if(L == NULL)
        errorPrompt("insertAfter()");
    if(isEmpty(L))
        printf("InsertAfter() called on empty List");
    if(L->index == -1)
        printf("InsertAfter() called on undefined index");
    if(L->cursor == L->back || L->length == 1){
        Node temp = newNode(data);
        L->cursor->next = temp;
        temp->previous = L->cursor;
        L->back = temp;
    }
    else{
        Node temp = newNode(data);
        L->cursor->next->previous = temp;
        temp->next = L->cursor->next;
        temp->previous = L->cursor;
        L->cursor->next = temp;
    }
    L->length++;
}
void deleteFront(List L){
    Node N = L->front;
    if(L == NULL)
        errorPrompt("deleteFront()");
    if(isEmpty(L))
        printf("deleteFront() called on empty List");
    else{
        if(L->cursor == L->front)
            L->cursor = NULL;
        if(L->length > 1){
            L->front = L->front->next;
            L->front->previous = NULL;
        }
        else{
            L->front = L->back = NULL;
        }
        L->length--;
        L->index--;
        freeNode(&N);
        
    }
}
void deleteBack(List L){
    Node N = L->back;
    if(L == NULL)
        errorPrompt("deleteBack()");
    if(isEmpty(L)){
        printf("deleteBack() called on empty List");
        exit(1);
    }
    else if(L->length == 1){
        L->front = L->back = NULL;
    }
    else{
        if(L->cursor == L->back)
            L->cursor = NULL;

        L->back = L->back->previous;
        L->back->next = NULL;
    }
    L->length--;
    freeNode(&N);
}
void delete(List L){
    if(L == NULL)
        errorPrompt("delete()");
    if(isEmpty(L)){
        printf("delete() called on empty List");
        exit(1);
    }
    Node N = L->cursor;
    if(L->index < 0)
        printf("delete() called on undefined index");
    else if(L->cursor == L->front)
        deleteFront(L);
    else if(L->cursor == L->back)
        deleteBack(L);
    else{
        L->cursor->previous->next = L->cursor->next;
        L->cursor->next->previous = L->cursor->previous;
        L->cursor = NULL;
        L->length--;
    }
    L->index = L->index - 1;
    freeNode(&N);
    
    
}
// Other operations ---------------------------------------------------------
void printList(FILE* out, List L){
    for(moveFront(L); index(L)>=0; moveNext(L)){
            fprintf(out, "%d " , get(L));
    }
}
List copyList(List L){
    List tempList = newList();
    Node tempNode = L->front;
    while(tempNode != NULL){
        append(tempList, tempNode->data);
        tempNode = tempNode->next;
    }
    return tempList;
}
