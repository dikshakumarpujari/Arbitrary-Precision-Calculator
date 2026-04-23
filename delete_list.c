#include "apc.h"
#include<stdlib.h>

int delete_list(APC **head, APC **tail)
{
    if (*head == NULL)// list is empty
    {
        return FAILURE;
    }

    APC *temp = *head;// start from head

    while (temp != NULL)
    {
        *head = temp->next;// move head to next node
        free(temp);// free current node
        temp = *head;// update temp
    }

    *tail = NULL;// list is now empty

    return SUCCESS;
}