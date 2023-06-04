/*******************************************************************************
*		Descriptions - AVL API Functions
*		Date: 07.12.2020
*       Group: OL96
*******************************************************************************/

#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stddef.h> /* size_t */

typedef struct avl_tree avl_t;

typedef enum
{
    PREORDER = 0,
    INORDER = 1,
    POSTORDER = 2
} traversal_t;

/* If the data which was sent as lhs is before rhs,
return value should be 1. otherwise (after or =) it should be 0. */
typedef int (*is_before_t)(const void *lhs, const void *rhs);

/* in cfile:
enum child_side_t {LEFT, RIGHT, NUM_OF_CHILDREN};

typedef struct node avl_node_t;
struct node
{
	void *data;
	avl_node_t *children[NUM_OF_CHILDREN];
    int height;
};

struct avl_tree
{
	avl_node_t *root;
	is_before_t is_before;
};
 end of cfile */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*
* Description: Create avl tree.
* Return value: Pointer to tree.
* Errors: Return NULL when fail allocate memory.
* Undefined behavior: Function pointer is NULL.
*
* Complexity: O(1).
*/
avl_t *AVLCreate(is_before_t is_before);

/*
* Description: Checks if tree has any nodes.
* Return value: 1 if empty, 0 if not empty.
* Errors: None.
* Undefined behavior: Tree pointer is NULL.
*
* Complexity: O(1).
*/
int AVLIsEmpty(const avl_t *tree);

/*
* Description: count the number of nodes in avl tree.
* Return value: number of nodes in tree.
* Errors:None
* Undefined behavior:Tree pointer is NULL.
*
* Complexity: O(n).
*/
size_t AVLSize(const avl_t *tree);

/*
* Description:  Calculate the height of the avl tree.
* Return value: the height of the tree.
*               -1 if tree is empty.
* Errors: None
* Undefined behavior: Tree pointer is NULL.
*
* Complexity: O(1).
*/
int AVLHeight(const avl_t *tree);

/*
* Description: Performs the inputted function on the data from each node
* Return value: 0 if actions performed sucessfully, 1 if not
* Errors: none
* Undefined behavior: If action changes the order of the nodes in the tree
*			Tree is NULL, if action_t is NULL
*
* Complexity: O(n).
*/
int AVLForEach(avl_t *tree, int (*action_t)(void *data, void *params),
                                 void *params, traversal_t traversal);

/*
* Description: Free all nodes and tree structure.
* Return value: none.
* Errors: None
* Undefined behavior: tree pointer is NULL.
*
* Complexity: O(n).
*/
void AVLDestroy(avl_t *tree);

/*
* Description: Inserts node into avl tree
* Return value: return 0 when SUCCESS, return 1 when FAILURE.
* Errors: Return 1 when memory allocation fails.
* Undefined behavior: Tree pointer is NULL, data of different type.
*
* Complexity: O(log n).
*/
int AVLInsert(avl_t *tree, const void *data);

/*
* Description: Finds the node which holds the argument as data.
* Return value: Return pointer to the requested data,
                    Return NULL if it doesn't exists.
* Errors: none
* Undefined behavior: tree is NULL
*
* Average case complexity: O(log n).
*/
void *AVLFind(const avl_t *tree, const void *key);

/*
* Description: Remove node from avl tree while keeping the tree balanced.
* Return value: pointer to the removed data if exists,
                            if it doesn't - return NULL.
* Errors: none
* Undefined behavior: tree is NULL.
*
* Complexity: O(log n).
*/
void *AVLRemove(avl_t *tree, const void *data);

#endif   /*__AVL_TREE_H__*/
