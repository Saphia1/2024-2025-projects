#include "sort.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* sort linked list *list using merge insertion sort. */
/* upon success, the elements in *list will be sorted. */
/* return silently if *list is uninitialised or empty. */
/* the compare argument is a pointer to a function which returns */
/* less than 0, 0, or greater than 0 if first argument is */
/* less than, equal to, or greater than second argument respectively. */
Node* merge(Node *node1,Node *node2,int (*compare)(void *, void *));
Node* getmid(Node *head,int listlen);
int getlength(Node *head);
void insertion_sort(LinkedList *list, int (*compare)(void *, void *))
{
    LinkedList *sorted=initialise_linked_list();
    Node *currentnode;
    Node *counternode;
    

    

    while ((list->head)!=NULL){
        currentnode=(list->head);
        list->head=list->head->next;

        if ((list->head)!=NULL){/*disconnecting linked list from the current node*/
            list->head->prev=NULL;/*setting new head to have no prev as heads have no prev*/
        }

        currentnode->next=NULL;/*disconnecting currentnode from the linked list, so doesn't accidentallu modify**/

        if ((sorted->head == NULL)){/*if sorted is empty*/
            sorted->head=currentnode;/*add currentnode to sorted*/
            sorted->tail=currentnode;



            
        }
        else if(compare((sorted->head->data), (currentnode->data))>0){/*if head of sorted is higher than current node, need to replace with current node*/
            currentnode->next=sorted->head;/*setting current node as head, and previous head as next*/
            sorted->head->prev=currentnode;/*setting prev of old head as current node*/
            sorted->head=currentnode;/*setting current node as head*/


        }
        else{/*if node needs to be added to either the end, or middle of sorted list*/
            counternode=(sorted->head);
            

            while ((counternode->next!=NULL) && (compare((counternode->next->data), (currentnode->data))<=0))/*while we haven't checked full list AND the item in list is less than item we are adding */
            {
                counternode=counternode->next;/*keep incrementing until find one needs to swap with or end list reached*/
            }   
                
            /*current node needs to go between counternode and counternode next*/
            currentnode->next=counternode->next;/*set the next pointer of the node we are inserting, current, to point to the node AFTER counternode*/
            if (counternode->next !=NULL){/*if the node we are inserting with is not at end of list, update the prev pointer of next node ro point at inserted node*/
                counternode->next->prev=currentnode; /*set the node that was after the one we swapped with,counter, to instead come after the node we are adding,current */
            }
                    
            else{/*if next value was non existent(adding to end of the list)*/
                sorted->tail=currentnode;/*appending*/
            }

                
            counternode->next=currentnode;/*set the counternode to point at node we just added*/
            currentnode->prev=counternode;/*set inserted node's prev to the node in front of it, counternode*/
            
        }
 

        
    }
    
    
    list->head=sorted->head;/*set to sorted so called by test program to print*/
    list->tail=sorted->tail;
    
    free(sorted);
   
}

/* sort linked list *list using merge sort algorithm. */
/* upon success, the elements in *list will be sorted. */
/* return silently if *list is uninitialised or empty. */
/* the compare argument is a pointer to a function which returns */
/* less than 0, 0, or greater than 0 if first argument is */
/* less than, equal to, or greater than second argument respectively. */
void merge_sort(LinkedList *list, int (*compare)(void *, void *))
{

    
    
    int length=getlength(list->head);
    Node *head =list->head;
    Node *middle;
    Node *left;
    Node *right;
    LinkedList *leftlist=initialise_linked_list();
    LinkedList *rightlist=initialise_linked_list();
    
    if ((length==0)){
        free_linked_list(leftlist);
        free_linked_list(rightlist);
        return;
    }
    
    left=head;
    middle=getmid(head,length);
    right=middle;
    middle->prev->next=NULL;
    middle->prev=NULL;


    leftlist->head=left;
    rightlist->head=right;


    merge_sort(leftlist,compare);
    merge_sort(rightlist,compare);


    left=leftlist->head;
    right=rightlist->head;
    list->head=merge((left),(right),compare);
    free(leftlist);
    free(rightlist);

}


Node* merge(Node *list1head,Node *list2head,int (*compare)(void *, void *)){

    Node*newnode=initialise_node();
    Node*currentnode=newnode;
    Node*node;

    newnode->next=NULL;

    while((list1head!=NULL) && (list2head !=NULL)){/*while the items in the list actually have stuff in them(not reached end)*/
        if(compare((list1head->data), (list2head->data))<=0){/*if list1's head node is bigger than list2's head node*/
            currentnode->next=list1head;/*then point current node to list 1's head*/
            list1head=list1head->next;/*set list 1's head to the next item in list 1*/
            /*list1head->prev=NULL;*/
        }
        else{/*if list 2 is actually bigger*/
            currentnode->next=list2head;/*then point current node to that item*/
            list2head=list2head->next;/*then set list 2's head to the next item in list 2*/
        
        }
        currentnode=currentnode->next;/*increment current node to be whichever of the two item's were bigger*/
    }
    if (list1head!=NULL){/*if we reached the end of list2 first and there is still items left in list 1*/
        currentnode->next=list1head;/*add the item to the sorted list*/
    }
    else{
        currentnode->next=list2head;/*if the opposite happened then add the items still left in list 2, OR if none, then just set the tail pointer to NULL*/
    }
    node=newnode->next;
    node->prev=NULL;
    newnode->next=NULL;
    ;
    free(newnode);
    
    return node;/*return newnode -> next which is the header of the combined sorted list*/

   




}
Node* getmid(Node *head, int length){
    Node*mid=head;
    int half;
    int i;
    if (length>1){
        half=(length/2);
    }
    else{
        half=1;
    }
    for (i=0;i!=half;i++){
        mid=mid->next;
       /* printf("\nmid:");
        print_string(mid->data);*/
        
    }
    return mid;

}

int getlength(Node *head){
    Node *currentnode=head;
    int length=0;
    /*if ((head==NULL)||(head->next==NULL)){
        return 1;
    }*/
    while (currentnode->next!=NULL){
        length+=1;
        currentnode=currentnode->next;

        
    }
    return length;
}

/*    printf("LEFT LIST\n");
    print_linked_list(leftlist,print_string);
    printf("\n");
    printf("RIGHT LIST\n");
    print_linked_list(rightlist,print_string);
    printf("---------\n");*/