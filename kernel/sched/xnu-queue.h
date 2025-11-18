/*
 * Copyright (c) 2000-2019 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
 
 /*
 */
 
 /*
 * Queue Management APIs
 *
 * There are currently two subtly different methods of maintaining
 * a queue of objects. Both APIs are contained in this file, and
 * unfortunately overlap.
 * (there is also a third way maintained in bsd/sys/queue.h)
 *
 * Both methods use a common queue head and linkage pattern:
 *      The head of a queue is declared as:
 *              queue_head_t q_head;
 *
 *      Elements in this queue are chained together using
 *      struct queue_entry objects embedded within a structure:
 *              struct some_data {
 *                      int field1;
 *                      int field2;
 *                      ...
 *                      queue_chain_t link;
 *                      ...
 *                      int last_field;
 *              };
 *      struct some_data is referred to as the queue "element."
 *      (note that queue_chain_t is typedef'd to struct queue_entry)
 *
 * IMPORTANT: The two queue iteration methods described below are not
 *            compatible with one another. You must choose one and be careful
 *            to use only the supported APIs for that method.
 *
 * Method 1: chaining of queue_chain_t (linkage chains)
 *      This method uses the next and prev pointers of the struct queue_entry
 *      linkage object embedded in a queue element to point to the next or
 *      previous queue_entry structure in the chain. The head of the queue
 *      (the queue_head_t object) will point to the first and last
 *      struct queue_entry object, and both the next and prev pointer will
 *      point back to the head if the queue is empty.
 *
 *      This method is the most flexible method of chaining objects together
 *      as it allows multiple chains through a given object, by embedding
 *      multiple queue_chain_t objects in the structure, while simultaneously
 *      providing fast removal and insertion into the queue using only
 *      struct queue_entry object pointers.
 *
 *      ++ Valid APIs for this style queue ++
 *      -------------------------------------
 *              [C] queue_init
 *              [C] queue_first
 *              [C] queue_next
 *              [C] queue_last
 *              [C] queue_prev
 *              [C] queue_end
 *              [C] queue_empty
 *
 *              [1] enqueue
 *              [1] dequeue
 *              [1] enqueue_head
 *              [1] enqueue_tail
 *              [1] dequeue_head
 *              [1] dequeue_tail
 *              [1] remqueue
 *              [1] insque
 *              [1] remque
 *              [1] re_queue_head
 *              [1] re_queue_tail
 *              [1] movqueue
 *              [1] qe_element
 *              [1] qe_foreach
 *              [1] qe_foreach_safe
 *              [1] qe_foreach_element
 *              [1] qe_foreach_element_safe
 *
 * Method 2: chaining of elements (element chains)
 *      This method uses the next and prev pointers of the struct queue_entry
 *      linkage object embedded in a queue element to point to the next or
 *      previous queue element (not another queue_entry). The head of the
 *      queue will point to the first and last queue element (struct some_data
 *      from the above example) NOT the embedded queue_entry structure. The
 *      first queue element will have a prev pointer that points to the
 *      queue_head_t, and the last queue element will have a next pointer
 *      that points to the queue_head_t.
 *
 *      This method requires knowledge of the queue_head_t of the queue on
 *      which an element resides in order to remove the element. Iterating
 *      through the elements of the queue is also more cumbersome because
 *      a check against the head pointer plus a cast then offset operation
 *      must be performed at each step of the iteration.
 *
 *      ++ Valid APIs for this style queue ++
 *      -------------------------------------
 *              [C] queue_init
 *              [C] queue_first
 *              [C] queue_next
 *              [C] queue_last
 *              [C] queue_prev
 *              [C] queue_end
 *              [C] queue_empty
 *
 *              [2] queue_enter
 *              [2] queue_enter_first
 *              [2] queue_insert_before
 *              [2] queue_insert_after
 *              [2] queue_field
 *              [2] queue_remove
 *              [2] queue_remove_first
 *              [2] queue_remove_last
 *              [2] queue_assign
 *              [2] queue_new_head
 *              [2] queue_iterate
 *
 * Legend:
 *      [C] -> API common to both methods
 *      [1] -> API used only in method 1 (linkage chains)
 *      [2] -> API used only in method 2 (element chains)
 */

/*
 *	A generic doubly-linked list (queue).
 */

struct queue_entry {
	struct queue_entry      *next;          /* next element */
	struct queue_entry      *prev;          /* previous element */
};

typedef struct queue_entry      *queue_t;
typedef struct queue_entry      queue_head_t;
typedef struct queue_entry      queue_chain_t;
typedef struct queue_entry      *queue_entry_t;

#define __QUEUE_ELT_VALIDATE(elt)       ((void)0)
#define __QUEUE_ELT_VALIDATE_NEXT(elt)  ((elt)->next)
#define __QUEUE_ELT_VALIDATE_PREV(elt)  ((elt)->prev)
#define __DEQUEUE_ELT_CLEANUP(elt)      ((void)0)
#define __queue_element_linkage_invalid(e) ((void)0)
