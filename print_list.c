#include "apc.h"
#include<stdlib.h>


void print_list(APC *head)
{
	/* Cheking the list is empty or not */
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
	else
	{
	    
	    while (head)		
	    {
		    /* Printing the list */
		    printf("%d", head -> data);

		    /* Traversing in forward direction */
		    head = head -> next;
	    }
    	printf("\n");
    }
}