#ifndef APC_H
#define APC_H

#include <stdio.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
}APC;

int insert_at_last(APC **head, APC **tail, int data);
int insert_at_first(APC **head, APC **tail, int data);
void print_list(APC *head);
int delete_list(APC **head, APC **tail);

void add(APC *tail1,APC *tail2,APC **reshead,APC **restail);
int compare(APC *head1,APC *head2);
void sub(APC *tail1,APC *tail2,APC **reshead,APC **restail);
void mul(APC *tail1,APC *tail2,APC **reshead,APC **restail);
void division(APC **tail1,APC **head1,APC *tail2,APC *head2,APC **reshead,APC **restail,APC **counthead,APC **counttail);
void add_one(APC **counthead,APC **counttail);
void remove_zero(APC **head);
#endif