/* *
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if(q==NULL) return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if(q==NULL) return;
    list_ele_t *p = q->head;
    while(p!= NULL)
    {
        list_ele_t *temp = p;
        p = p ->next;
        if(temp->value != NULL)
        {
            free(temp->value);
        }
        free(temp);
    }
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{

    /* What should you do if the q is NULL? */
    if(q==NULL || s == NULL)
    {
      return false;
    }
    list_ele_t* new = (list_ele_t *)malloc(sizeof(list_ele_t));
    if(new==NULL) return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    new -> value = (char*)malloc(sizeof(char)*(strlen(s) + 1));
    if(new->value == NULL)
    {
      free(new);
      return false;
    }
    strncpy(new->value, s, strlen(s) + 1);
    new->next = q->head;
    q->head = new;
    if(q->tail == NULL) q->tail = new;
    q->size += 1;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if(q==NULL || s == NULL) return false;
    list_ele_t *new_node = (list_ele_t *) malloc(sizeof(list_ele_t));
    if (new_node == NULL) 
    {
        return false;
    }
    new_node -> value = (char *) malloc(sizeof(char) * (strlen(s) + 1));
    if (new_node -> value == NULL)
    {
      free(new_node);
      return false;
    }
    strncpy(new_node->value, s, strlen(s) + 1);
    new_node -> next = NULL;
    if (q->tail == NULL)
    {
        q->head = new_node;
        q->tail = new_node;
    }
    else
    {
      q->tail->next = new_node;
      q->tail = new_node;
    }
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    q->size ++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if(q==NULL || q->head==NULL || q-> size ==0) 
    {
      return false;
    }
    if (sp == NULL && bufsize == 0) {
    }
    else {
        memset(sp, '\0', bufsize);
        strncpy(sp, q->head->value, bufsize - 1);
    }
    list_ele_t *removed = q->head;
    q->size--;
    if (q->size == 0)
    {
      q->head = NULL;
      q->tail = NULL;
    }
    else 
    {
      q->head = q->head ->next;
    }
    free(removed->value);
    free(removed);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if(q==NULL) return 0;
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->head==NULL || q->size < 2) return;
    list_ele_t *current = q->head;
    list_ele_t *prev = NULL;
    list_ele_t *next = current->next;
    list_ele_t *headq = q -> head;
    list_ele_t *endq = q->tail;
    q->head = endq;
    q->tail = headq;
    while (current->next != NULL)
    {
        current->next = prev;
        prev = current;
        current = next;
        next = current->next;
    }
    current->next = prev;
    return;
    
}
