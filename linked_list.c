// do not include other libraries
#include <stdio.h>
#include <stdlib.h>

// ***************************************
// *** struct definitions ****************
// *** do not change these ***************
// ***************************************
typedef struct NODE {int data; struct NODE* next;} NODE; // nodes of the linked list
typedef struct LINKED_LIST {struct NODE *head;} LINKED_LIST; // struct to act as the head of the list


// ***************************************
// *** provided functions  ****************
// ***************************************

// this function returns a LINKED_LIST struct to
// act as the head of the linked list.
// do not change this function
LINKED_LIST Create_List(void) {LINKED_LIST list = {NULL}; return list;}

// call this function to verify malloc worked when you create new nodes
void Verify_Malloc(NODE *node) {if (node == NULL) {printf("Malloc Failed\n"); exit(1);} return;}

// do not change this function
// this function prints out all of the nodes in the linked list
void Print_List(FILE *out, LINKED_LIST list) {
    if (list.head == NULL) {printf("\n"); return;} //empty list
    NODE *current = list.head;
    while (current->next != NULL) {
        fprintf(out, "%d -> ",current->data);
        current = current->next;
    }
    fprintf(out, "%d\n",current->data);
    return;
}

// ******************************************************
// *** Complete the following functions  ****************
// ******************************************************

// this function returns the number 
// of elements in the linked list
int Size(LINKED_LIST list){
    int size = 0;
    if(list.head == NULL){
        return size; //empty list
    }
    NODE *current = list.head;
    while(current -> next != NULL){
        size++;
        current = current -> next;
    }
    size++;
    return size;
}
// this function adds an element to
// the front of the list

void Push_Front(LINKED_LIST *list, int data){
    NODE *new_node = malloc(sizeof(NODE));
    Verify_Malloc(new_node);
    new_node -> data = data;
    if(list -> head == NULL){
        new_node -> next = NULL;
        list -> head = new_node;
    }
    else{
        new_node -> next = list->head;
        list -> head = new_node;
    }
    //return;
}

// this function adds an element 
// to the end of the linked list 

void Push_Back(LINKED_LIST *list, int data) {
    NODE *new_node = malloc(sizeof(NODE));
    Verify_Malloc(new_node);
    new_node -> data = data;
    new_node -> next = NULL;
    
    if(list -> head == NULL){
        list -> head = new_node;
    }
    else{
        NODE *current = list -> head;
        while(current -> next != NULL){
            current = current -> next;
        }
        current -> next = new_node;
    }
    //return;
}

// if the list is not empty
// the value of the first element of the list is returned by reference in the parameter data
// the first element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int Pop_Front(LINKED_LIST *list, int *data) {
    if(list -> head == NULL){
        return 0; //empty list
    }
    NODE *current = list -> head;
    *data = current -> data;
    list -> head = current -> next;
    free(current);
    return 1;
}

// if the list is not empty
// the value of the last element of the list is returned by reference in the parameter data
// the last element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int Pop_Back(LINKED_LIST *list, int *data) {
    if(list -> head == NULL){
        return 0; //empty list
    }
    NODE *current = list -> head;
    if(current -> next == NULL){
        *data = current -> data;
        free(current);
        list -> head = NULL;
        return 1;
    }
    while(current -> next -> next != NULL){
        current = current -> next;
    }
    *data = current -> next -> data;
    free(current -> next);
    current->next = NULL;
    
    return 1;
   
}

// this function returns the number 
// of times that the value of the parameter 
// data appears in the list
int Count_If(LINKED_LIST list, int data) {
    int count = 0;
    if(list.head == NULL){
        return count; //empty list
    }
    NODE *current = list.head;
    while(current -> next != NULL){
        if(current->data == data){
            count++;
        }
        current = current->next;
    }
    if(current->data == data){
        count++;
    }
    return count;
}

// delete the first node containing the data value
// return 1 if something was deleted otherwise 0
// remember to free the deleted node
int Delete(LINKED_LIST *list, int data) {
    if(list->head == NULL){
        return 0; //empty list
    }
    NODE *current = list -> head;
    if(current -> data == data){
        list -> head = current->next;
        free(current);
        return 1;
    }
    while(current -> next != NULL){
        if(current -> next -> data == data){
            NODE *temp = current->next;
            current->next = temp->next;
            free(temp);
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// return 1 if the list is empty otherwise returns 0
int Is_Empty(LINKED_LIST list) {
    if(list.head == NULL){
        return 1; //empty list
    }
    return 0;
}

// delete all elements of the list
// remember to free the nodes
void Clear(LINKED_LIST *list) {
    if(list->head == NULL){
        return; //empty list
    }
    NODE *current = list -> head;
    while(current -> next != NULL){
        NODE *temp = current;
        current = current -> next;
        free(temp);
    }
    free(current);
    
    list -> head = NULL;
    return; 
    
}

// if an element appears in the list 
// retain the first occurance but
// remove all other nodes with the same 
// data value
void Remove_Duplicates(LINKED_LIST *list) {
    if(list -> head == NULL){
        return; //empty list
    }
    NODE *current = list -> head;
    while(current -> next != NULL){
        if(current -> data == current -> next -> data){
            NODE *temp = current -> next;
            current -> next = temp -> next;
            free(temp);
        }
        else{
            current = current -> next;
        }
    }
    return;
}

// modify main to completely test your functions 
int main() {
    // create a linked list
    printf("creating linked list\n");
    LINKED_LIST list = Create_List();
   
    // add some data (hardcoded for testing)
    printf("hardcoding some data\n");
    NODE *first  = malloc(sizeof(NODE)); Verify_Malloc(first);
    NODE *second = malloc(sizeof(NODE)); Verify_Malloc(second);
    first->data  = 1;
    second->data = 2;
    list.head = first;
    first->next = second;
    second->next = NULL;

    // print the list
    printf("Testing Print_List\n");
    Print_List(stdout, list);

    // write a better test for Size
    printf("Testing Size\n");
    printf("size = %d\n",Size(list));

    // write a better test for Push_Front
    printf("Testing Push_Front\n");
    Push_Front(&list, 0);
    Print_List(stdout, list);
    
    // write a better test for Push_Back
    printf("Testing Push_Back\n");
    Push_Back(&list, 3);
    Print_List(stdout, list);

    // write a better test for Pop_Front
    printf("Testing Pop_Front\n");
    {
        int x; 
        int not_empty = Pop_Front(&list, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            Print_List(stdout,list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }

    // write a better test for Pop_Back
    printf("Testing Pop_Back\n");
    {
        int x; 
        int not_empty = Pop_Back(&list, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            Print_List(stdout,list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }

    // write a beter test for Count_If
    Push_Front(&list, 5);
    Push_Front(&list, 5);
    Print_List(stdout, list);
    printf("5 count = %d\n",Count_If(list, 5));
    
    // write a test for Delete 
    printf("Testing Delete\n");
    Print_List(stdout, list);
    Delete(&list, 1); 
    Print_List(stdout, list);

    // write a better test for Is_Empty
    printf("Testing Is_Empty\n");
    if (Is_Empty(list)) printf("List is Empty\n"); else printf("List is not empty\n");
    
    // write a better test for Clear
    Clear(&list);
    if (Is_Empty(list)) printf("List is Empty\n"); else printf("List is not empty\n");

    // write a better test for Remove_Duplicates
    Push_Back(&list, 1);
    Push_Back(&list, 1);
    Push_Back(&list, 1);
    Push_Back(&list, 2);
    Push_Back(&list, 2);
    Push_Back(&list, 3);
    Push_Back(&list, 3);
    Push_Back(&list, 3);
    Remove_Duplicates(&list);
    Print_List(stdout, list);
    return 0;
}
