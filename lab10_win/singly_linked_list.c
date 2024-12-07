/* SYSC 2006 Lab 10
   A module that implements a singly-linked list of integers. 
 */

#include <assert.h>  // assert
#include <stdlib.h>  // malloc, free
#include <stdbool.h>
#include <stdio.h>   // printf

#include "singly_linked_list.h"

/*************************************************************
 * Functions presented in lectures.
 *************************************************************/

/* Parameter head points to the first node in a linked list, or is NULL
   if the linked list is empty. Insert a node containing the specified 
   integer value at the front of the linked list, and return a pointer to 
   the first node in the modified list.

   Terminate (via assert) if memory for the node cannot be allocated.
 */
intnode_t *push(intnode_t *head, int value)
{
    intnode_t *p = malloc(sizeof(intnode_t));
    assert (p != NULL);
    p->value = value;
    p->next = head;
    return p;
}

/* Parameter head points to the first node in the list.
   Return the length of a linked list (0 if the linked list is empty). 
 */
int length(intnode_t *head)
{
    int count = 0;
    for (intnode_t *curr = head; curr != NULL; curr = curr->next) {
        count += 1;
    }
    return count;
}

/* Parameter head points to the first node in a linked list.
   Print the linked list, using the format:
       value1 -> value2 -> value3 -> ... -> last_value
 */
void print_list(intnode_t *head)
{
    if (head == NULL) {
        printf("empty list");
        return; 
    }

    intnode_t *curr;

    /* The loop prints a every node in the linked list except the last one,
       using the format "value -> ", where "->" represents the link from each node
       to the following node.

       Notice that the loop condition is:
           curr->next != NULL
       and not:
           curr != NULL

       During the last iteration, the value in the second-last node is
       printed, then curr is updated to point to the last node. The
       condition curr->next != NULL now evaluates to false, so the 
       loop exits, with curr pointing to the last node (which has  
       not yet been printed.) 
     */

    for (curr = head; curr->next != NULL; curr = curr->next) {
        printf("%d -> ", curr->value);
    }

    /* Print the last node. */
    printf("%d", curr->value);
}



/*****************************************************************
 * Solutions to New Exercises
 *****************************************************************/

// Exercise 1

/* Parameter head points to the first node in a linked list, or is
 * NULL if the list is empty.
 *
 * Count the number of nodes in the linked list that contain an integer
 * equal to target, and return that count.
 * 
 * Return 0 if the linked list is empty.
 */ 
int count(intnode_t *head, int target)
{
    int count = 0;
    if(head == NULL){
        return count;
    }
    for(intnode_t *curr = head; curr != NULL; curr = curr->next){
        if(curr->value == target){
            count++;
        }
    }
    return count;
} 

// Exercise 2

/* Parameter head points to the first node in a linked list, or is
 * NULL if the list is empty.
 *
 * Return the largest integer in the linked list.
 *
 * The function terminates (via assert) if the linked list is empty.
 */
int max_value(intnode_t *head)
{
    assert(head != NULL);
    int largest = head->value;
    for(intnode_t *curr = head; curr != NULL; curr = curr->next){
        if(curr->value > largest){
            largest = curr->value;
        }
    }
    return largest;
}


// Exercise 3

/* Parameter head points to the first node in a linked list, or is
 * NULL if the list is empty.
 *
 * Return the index (position) of the first node that contains an 
 * integer equal to target. The first node is at index 0, the second node
 * is at index 1, etc.
 *
 * Return -1 if target is not in the linked list, or if the linked list
 * is empty.
 */
int value_index(intnode_t *head, int target)
{
    int i = 0;
    for(intnode_t *curr = head; curr != NULL; curr = curr->next){
        if(curr->value == target){
            return i;
        }
        i++;
    }
    return -1;
}


// Exercise 4

/* Parameter head points to the first node in a linked list, or is
 * NULL if the list is empty.
 *
 * Parameter other points to the first node in a linked list, or is
 * NULL if the list is empty.
 *
 * Extend the linked list pointed to by head so that it contains
 * copies of the values stored in the linked list pointed to by other.
 *
 * The function terminates (via assert) if the the linked list 
 * pointed to by head is empty.
 */
void extend(intnode_t *head, intnode_t *other)
{
    assert(head != NULL);

    //Navigate to the end of the first list
    intnode_t *currog = head;
    while(currog->next != NULL){
        currog = currog->next;
    }
    
    //Go through other list and make copies of all nodes and append them to the original
    for(intnode_t *currother = other; currother != NULL; currother = currother->next, currog = currog->next){
        intnode_t *newnode = malloc(sizeof(intnode_t));
        assert(newnode != NULL);
        newnode->value = currother->value;
        newnode->next = NULL;
        currog->next = newnode; 
    }
}

// Exercise 5

/* Parameter head points to the first node in a linked list, or is
 * NULL if the list is empty.
 *
 * The function terminates (via assert) if the linked list is empty.
 *
 * Copy the value in the head node to the location pointed to by
 * parameter popped_value, delete the head node, and return a pointer
 * to the first node in the modified list.
 */
intnode_t *pop(intnode_t *head, int *popped_value)
{
    assert(head != NULL);

    *popped_value = head->value;
    head = head->next;

    return head;
}

