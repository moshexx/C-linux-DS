/*******************************************************************************
*		Descriptions - Binary Sorted Tree API Functions	        *
*		Date: 29.11.2020						*
*		Group: OL96							*
*******************************************************************************/

#ifndef __BINARY_SORTED_TREE_H__
#define __BINARY_SORTED_TREE_H__
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stddef.h>

typedef struct binary_sorted_tree bst_t;

typedef void *bst_iter_t;

/* If the data which was sent as lhs is < rhs,
return value should be 1. otherwise (>=) it should be 0. */
typedef int (*is_before_t)(const void *lhs, const void *rhs);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*
* Description: Create binary tree.
* Return value: Pointer to tree.
* Errors: Return NULL when fail allocate memory.
* Undefined behavior: Function pointer is NULL.
*
* Complexity: O(1).
*/
bst_t *BSTCreate(is_before_t is_before);

/*
* Description: Free all nodes and tree structure.
* Return value: none.
* Errors: None
* Undefined behavior: Tree pointer is NULL.
*
* Complexity: O(n).
*/
void BSTDestroy(bst_t *tree);

/*
* Description: Find number of nodes in binary tree.
* Return value: number of nodes in tree.
* Errors:None
* Undefined behavior:Tree pointer is NULL.
*
* Complexity: O(n).
*/
size_t BSTSize(const bst_t *tree);

/*
* Description: Checks if tree has any nodes.
* Return value: 1 if empty, 0 if not empty.
* Errors: None.
* Undefined behavior: Tree pointer is NULL.
*
* Complexity: O(1).
*/
int BSTIsEmpty(const bst_t *tree);

/*
* Description: Inserts node into binary tree
* Return value: Iterator pointing to the node which has been inserted
* Errors: Return end-node (stub) when memory allocation fails.
* Undefined behavior: Tree pointer is NULL and/or data of different type.
*
* Complexity: O(log n). Worst case: 0(n).
*/
bst_iter_t BSTInsert(bst_t *tree, const void *data);

/*
* Description: Remove node from binary tree leaving all other nodes in
*								valid order
* Return value: none
* Errors: none
* Undefined behavior: iter is NULL.
*
* Complexity: O()
*/
void BSTRemove(bst_iter_t iter);

/*
* Description: Finds first node in order in tree
* Return value: pointer to node
* Errors: none
* Undefined behavior: Tree is NULL.
*
* Average complexity: O(log n). Worst_case Complexity: O(n).
*/
bst_iter_t BSTBegin(const bst_t *tree);

/*
* Description: Finds last node in order in tree
* Return value: pointer to node
* Errors:
* Undefined behavior:Tree is NULL.
*
* Complexity: O(1)
*/
bst_iter_t BSTEnd(const bst_t *tree);

/*
* Description: Finds node after argument in tree in order
* Return value: pointer to node
* Errors: none
* Undefined behavior: iter is NULL or iter is stub.
*
*Complexity: O(log n). Best Case: O(1)
*/
bst_iter_t BSTNext(bst_iter_t iter);

/*
* Description: Finds node before  argument in tree in order
* Return value: pointer to node
* Errors: none
* Undefined behavior:iter is NULL or iter is first iter in tree.
*
* Complexity: O(log n). Best Case: O(1)
*/
bst_iter_t BSTPrev(bst_iter_t iter);

/*
* Description: Checks if two pointers point to the same node
* Return value: 1 if pointers are identical, 0 if not
* Errors: none
* Undefined behavior: none
*
* Complexity: O(1).
*/
int BSTIsSameIter(bst_iter_t lhs, bst_iter_t rhs);

/*
* Description: Gets data from a pointer to a node
* Return value: void pointer to data
* Errors: none
* Undefined behavior: iter is NULL
*
* Complexity: O(1).
*/
void *BSTGetData(bst_iter_t iter);

/*
* Description: Finds the node which holds the argument as data
* Return value: the node with the requested data, or stub if none
* Errors: none
* Undefined behavior: tree is NULL
*
* Average case complexity: O(log n). Worst_case Complexity: O(n).
*/
bst_iter_t BSTFind(const bst_t *tree, const void *data);

/*
* Description: Performs the inputted function on the data from each node
* Return value: 0 if actions performed sucessfully, 1 if not
* Errors: none
* Undefined behavior: If action changes the order of the nodes in the tree
			Tree is NULL, if action_t is NULL
*
* Complexity: O(n).
*/
int BSTForEach(bst_t *tree, int (*action_t)(void *data, void *params),
								void *params);

#endif   /*__BINARY_SORTED_TREE_H__*/
