/* 
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
    queue_t *q =  (queue_t*)malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if(q == NULL) {
    	return NULL;
    }
    q->head = q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    if(q == NULL) {
    	return;
    }
  	list_ele_t* p = q->head,*cur;
  	while(p != NULL) {
  		cur = p;
        p = p->next;
        free(cur->value);
        free(cur);
  	}
    /* Free queue structure */
    free(q);
    q = NULL;
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
    if(q == NULL) {
		return false;
	}
    list_ele_t* newh = (list_ele_t*)malloc(sizeof(list_ele_t));
    if(newh == NULL) {
    	return false;
    }
    newh->value = (char*)malloc((strlen(s) + 1) * sizeof(char));   //allocate space for the string
    if(newh->value == NULL) {
        free(newh);
    	return false;
    }
    strcpy(newh->value,s);   //copy the string
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if(q->size == 0) {    //update q->tail
		q->tail = newh;
	}
    newh->next = q->head;
    q->head = newh;     //update q->head
    q->size++;
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
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if(q == NULL) {
    	return false;
    }
    list_ele_t* newt = (list_ele_t*)malloc(sizeof(list_ele_t));
    if(newt == NULL) {
		return false;
	}
    newt->value = (char*)malloc((strlen(s) + 1) * sizeof(char));   //allocate space for the string
    if(newt->value == NULL) {
        free(newt);
    	return false;
    }
    strcpy(newt->value,s);   //copy the string
    newt->next = NULL;
    if(q->tail == NULL) {
    	q->head = q->tail = newt;
    } else {
    	q->tail->next = newt;
        q->tail = newt;   //update q->tail
    }
    q->size++;
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
    if(q == NULL || q->head == NULL) {
    	return false;
    }
    list_ele_t* temp = q->head;
    if(sp != NULL) {
        strncpy(sp,temp->value,bufsize);
        sp[bufsize - 1] = '\0';
    }
    q->head = q->head->next;
    free(temp->value);
    free(temp);
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if(q != NULL && q->head != NULL) {
    	return q->size;
    }
    return 0;
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
    /* You need to write the code for this function */
    if(q == NULL || q->head == NULL || q->head->next == NULL) {
    	return;
    }
    list_ele_t* beg = NULL;
    list_ele_t* end = q->head;
    list_ele_t* p = q->head;
    while(end != NULL) {
    	list_ele_t* the_next = end->next;
    	end->next = beg;
    	beg = end;
    	end = the_next;
    }
    q->head = beg;
    q->tail = p;
}

