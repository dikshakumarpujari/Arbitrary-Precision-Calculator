#include<stdio.h>
#include "apc.h"
#include <stdlib.h>
#include<string.h>

// Function to add two numbers represented as linked lists
void add(APC *tail1,APC *tail2,APC **reshead,APC **restail)
{
    APC *temp1=tail1;//store tail1 in temp1
    APC *temp2=tail2;//Store tail2 in temp2
    int res=0,carry=0;//Declare the variables
    while(temp1!=NULL || temp2!=NULL)//Loop to traverse the node upto null
    {
        if(temp1!=NULL && temp2!=NULL)// If both digits are present
        {
            res=temp1->data + temp2->data + carry;// Add digits with carry
            temp1=temp1->prev;// Move to previous digit of operand1
            temp2=temp2->prev;// Move to previous digit of operand2
        }
        else if(temp1!=NULL)// check if only operand1 digit is present
        {
            res=temp1->data + carry;// Add carry to operand1 digit
            temp1=temp1->prev;// Move to previous digit
        }
        else if(temp2!=NULL)// check if only operand2 digit is present
        {
            res=temp2->data + carry;// Add carry to operand2 digit
            temp2=temp2->prev;// Move to previous digit
        }
        if(res>9) // check if sum is greater than 9
        {
            res=res%10;// Store last digit
            carry=1;
        }
        else
        carry=0;
        insert_at_first(reshead,restail,res);// Insert result digit at beginning

    }
    if(carry==1)
    insert_at_first(reshead,restail,carry);// Insert carry
}

// Function to compare two numbers
int compare(APC *head1,APC *head2)
{
     int len1=0, len2=0;// Variables to store lengths
    APC *temp1=head1;
    APC *temp2=head2;

    while(temp1!=NULL)// Count length of first number
    {
        len1++;//increment
        temp1=temp1->next;//move to next node
    }
    while(temp2!=NULL)// Count length of second number
    {
        len2++;//Increment
        temp2=temp2->next;//Move to next node
    }

    if(len1<len2)// check If first number is smaller
    {
        return -1;
    }

    else if(len1==len2)// check If both numbers have equal length
    {
        while(head1!=NULL && head2!=NULL)// Compare digit by digit
        {
            if(head1->data < head2->data)// check If first is smaller
            {
                return -1;
            }
            else if(head1->data > head2->data)// check If first is larger
            return 1;

            head1=head1->next;// Move to next digit
            head2=head2->next;
        } 
        return 0;  
    }
    else
    return 1;
}

// Function to subtract two numbers
void sub(APC *tail1,APC *tail2,APC **reshead,APC **restail)
{
    APC *temp1=tail1;
    APC *temp2=tail2;
    int res=0,flag=0,val1,val2;//Declaring the variables
     while(temp1!=NULL || temp2!=NULL)// Loop to traverse
    {
        val1=0,val2=0;// Initialize digit values
        if(temp1!=NULL)// If digit exists in operand1
        val1=temp1->data;
        if(temp2!=NULL)// If digit exists in operand2
        val2=temp2->data;

        if(flag==1)// check if borrow from previous digit
        val1=val1 - 1;
        if(temp1!=NULL && temp2!=NULL) // check if both digits are present
        {
            if(val1 < val2) // check if borrow is required
            {
                res=val1 +10-val2;// Borrow and subtract
                flag=1;
            }
            else
            {
                res=val1-val2;//Substraction
                flag=0;
            }
            temp1=temp1->prev;// Move to previous node
            temp2=temp2->prev;// Move to previous node
        }
        else if(temp1!=NULL && temp2==NULL)// check if only operand1 digit exists
        {
            res=val1;// Result is operand1
            if(res<0)
            {
            res=9;
            flag=1;
            }
            else
            flag=0;
            temp1=temp1->prev;// Move to previous node
        }
        insert_at_first(reshead,restail,res);// Insert result digit
    }
}

// Function to multiply two numbers
void mul(APC *tail1,APC *tail2,APC **reshead,APC **restail)
{
    APC *temp2=tail2;
    APC * reshead1=NULL;
    APC *restail1=NULL;
    APC *reshead2=NULL;
    APC *restail2=NULL;
    int res=0,carry,count=0;//Declaring the variables
    while(temp2!=NULL)// Loop through second operand
    {
        APC *temp1=tail1;// Pointer for first operand
        carry=0;
        if(count!=0)// check if not first digit
        {
            for(int i=0;i<count;i++)
            insert_at_first(&reshead2,&restail2,0);
        }
        while(temp1!=NULL) // Multiply with each digit
        {
            res=(temp2->data*temp1->data)+carry;// Multiply and add carry
            if(res>9)// If result exceeds single digit
            {
                carry=res/10;// Update carry
                res=res%10;
            }
            else
            carry=0;
            if(count==0)
            insert_at_first(&reshead1,&restail1,res);

            else
            insert_at_first(&reshead2,&restail2,res);

            temp1=temp1->prev;//Move to the previous node

        }
        if(carry!=0)// If carry remains
        {
            if(count==0)
            insert_at_first(&reshead1,&restail1,carry);

            else
            insert_at_first(&reshead2,&restail2,carry);
        }
        count++;// Increment position counter
        if(count>=2)// check if more than one partial product
        {
            add(restail1,restail2,reshead,restail);
            delete_list(&reshead1,&restail1);// Delete old list
            delete_list(&reshead2,&restail2);
            reshead1=*reshead;// Update result head
            restail1=*restail;// Update result tail
            *reshead=NULL;// Reset result pointers
            *restail=NULL;
        }
        temp2=temp2->prev;// Move to next digit of operand2
    }  
    *reshead=reshead1;// Assign final result head
    *restail=restail1;// Assign final result tail
    
}

// Function to divide two numbers
void division(APC **tail1,APC **head1,APC *tail2,APC *head2,APC **reshead,APC **restail,APC **counthead,APC **counttail)
{
     while(compare(*head1,head2)==1 || compare(*head1,head2)==0)
    {
        add_one(counthead,counttail);// Increment quotient
        sub(*tail1,tail2,reshead,restail);// Subtract divisor from dividend
        delete_list(head1,tail1);// Delete old dividend
        *tail1=*restail;// Update tail
        *head1=*reshead;// Update head
        *reshead=NULL;
        *restail=NULL;
        remove_zero(head1);      
    }
    
}
// Function to increment count
void add_one(APC **counthead,APC **counttail)
{
    APC *temp=*counttail;
    int carry=1;// Initialize carry
    while(temp!=NULL && carry==1)// Loop until carry 
    {
        temp->data=temp->data+carry;// Add carry
        if(temp->data > 9) // If overflow
        {
            temp->data=0;// Reset digit
            carry=1;
        }
        else
        carry=0;

        temp=temp->prev;// Move to previous digit
    }
    if(carry==1)
    insert_at_first(counthead,counttail,carry);
}

// Function to remove leading zeros from a number
void remove_zero(APC **head)
{
    
    while(*head && (*head)->data==0 && (*head)->next!=NULL)
    {
        APC *temp=*head;
        *head=temp->next;// Move head forward
        (*head)->prev=NULL;// Reset previous pointer
        free(temp);// Free removed node
    }
}
