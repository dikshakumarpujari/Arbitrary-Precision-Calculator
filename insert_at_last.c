#include "apc.h"
#include<stdlib.h>


int insert_at_last(APC **head, APC **tail, int data)
{
    APC *new=malloc(sizeof(APC));//Create the node
    if(new==NULL)//Check new created
    return FAILURE;
    new->data=data;//Update data
    new->prev=NULL;//Update previous
    new->next=NULL;//Update next
    if(*head==NULL)//Check whether it contains node
    {
        *head=new;//Update head
        *tail=new;//Update tail
    }
    else
    {
        (*tail)->next=new;//Update next
        new->prev=*tail;
        *tail=new;
    }
    return SUCCESS;

}