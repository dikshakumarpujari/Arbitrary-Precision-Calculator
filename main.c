/*
NAME : DIKSHA
PROJECT : APC (Arbitrary Precision Calculator)
DESCRIPTION:
This project implements an Arbitrary Precision Calculator (APC) in C to perform arithmetic
operations on very large numbers that exceed built-in data type limits. Numbers are stored as 
doubly linked lists, with each node representing a single digit. The calculator supports addition, subtraction,
multiplication, and division, including handling of positive and negative values. All operations are 
performed digit-by-digit using linked list traversal. This approach avoids overflow and enables accurate 
computation for large integers.
*/



#include <stdio.h>
#include "apc.h"
#include <string.h>
int main(int argc,char *argv[])
{
    // Head pointers for operand 1 and operand 2
    APC *head1=NULL;
    APC *head2=NULL;
    // Tail pointers for operand 1 and operand 2
    APC *tail1=NULL;
    APC *tail2=NULL;
    // Head and tail pointers for result 
    APC *reshead=NULL;
    APC *restail=NULL;

// Head and tail pointers for quotient/count list
    APC *counthead=NULL;
    APC *counttail=NULL;
    insert_at_first(&counthead,&counttail,0);
    
    if(argc!=4)// Check for valid number of command line arguments
    {
        printf("ERROR: Invalid arguments\n");
        printf("Usage: ./a.out [operand 1] [operater] [operand 2]\n");
        return 0;
    }
     int i=0,j=0,data,flag1=0,flag2=0;//Declaring the varriables
     if(argv[1][i]=='+' || argv[1][i]=='-')// Check sign of operand 1
     {
        flag1=1;
        i++;
     }
    while(argv[1][i]!='\0')// Traverse operand 1 string
    {
        if(argv[1][i]>='0' && argv[1][i]<='9')// Check digit
        {
            data=argv[1][i]-'0';// Convert char to integer
            insert_at_last(&head1,&tail1,data);// Insert digit into list
        }
        else
        {
           printf("Invalid Operand1\n") ;
           return 0;
        }
        i++;// Move to next character
    }
    remove_zero(&head1);
    if(argv[3][j]=='+' || argv[3][j]=='-')
     {
        flag2=1;
        j++;
     }
    while(argv[3][j]!='\0')// Check sign of operand 2
    {
        if(argv[3][j]>='0' && argv[3][j]<='9')// Check digit
        {
            data=argv[3][j]-'0';// Convert char to integer
            insert_at_last(&head2,&tail2,data);// Insert digit into list
        }
        else
        {
           printf("Invalid Operand2\n") ;
           return 0;
        }
        j++;// Move to next character
    }
    remove_zero(&head2);
    if(strlen(argv[2])!=1)//Finding the length
    {
        printf("Invalid operator\n");
        return 0;
    }
    printf("Result: ");

    switch(argv[2][0])// Check operator
    {
        case '+' :
        // If both operands have same sign, perform addition
        if(flag1==flag2)
        add(tail1,tail2,&reshead,&restail);
        else
        {
            if(compare(head1,head2)==0)//Compare head1 and head2
            {
                printf("0\n");
                return 0;
            }
            else if(compare(head1,head2)==-1)// If operand 2 is larger, subtract operand 1 from operand 2
            {
                sub(tail2,tail1,&reshead,&restail);
                remove_zero(&reshead);
                if(flag2==1)
                printf("-");
            }
        else//subtract operand 2 from operand 1
        {
            sub(tail1,tail2,&reshead,&restail);//Perform the subraction function
            remove_zero(&reshead);
            if(flag1==1)
            printf("-");
        }
        }
        // Print negative sign if both operands are negative
        if(flag1==1 && flag2==1 && reshead->data!=0)
        printf("-");
        print_list(reshead);
        break;

        case '-':
        // Positive minus negative = addition
        if(flag1==0 && flag2==1)
        add(tail1,tail2,&reshead,&restail);
    // Negative minus positive = negative addition
        else if(flag1==1 && flag2==0)
        {
            add(tail1,tail2,&reshead,&restail);
            printf("-");
        }
        else
        {
            //if they are equal, result is zero
            if(compare(head1,head2)==0)
            {
                printf("0\n");
                return 0;
            }
             // If operand 2 is larger
            else if(compare(head1,head2)==-1)
            {
                sub(tail2,tail1,&reshead,&restail);//Perform substraction
                remove_zero(&reshead);
                if(flag1==0)// If operand1 is positive
                printf("-");
            }
            else// If operand1 > operand2
            {
                sub(tail1,tail2,&reshead,&restail);// Subtract operand2 from operand1
                remove_zero(&reshead);
                if(flag1==1)// If operand1 is negative
                printf("-");
            }
        }
        print_list(reshead);
        break;

        case 'x':
        case 'X':
        mul(tail1,tail2,&reshead,&restail);// Perform multiplication
        remove_zero(&reshead);
        if((flag1==1 && flag2==0 && reshead->data!=0))// Sign check
        printf("-");
        else if(flag1==0 && flag2==1 && reshead->data!=0)
        printf("-");
        print_list(reshead);
        break;

        case '/':
        if(head2->data==0)
        {
            printf("Error:Divide by zero is not Possible\n");
            return 0;
        }
        division(&tail1,&head1,tail2,head2,&reshead,&restail,&counthead,&counttail);
        if(flag1==1 && flag2==0 && counthead->data!=0)// Check divisor is zero
        printf("-");
        else if(flag1==0 && flag2==1 && counthead->data!=0)// Sign check
        printf("-");
        print_list(counthead);//call printlist function to Print quotient
        
        break;

        default:
        printf("\nINVALID OPERATOR\n");
    }
    return 0;

}