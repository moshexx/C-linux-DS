/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: avl_tree.c
*	author: Moshe Cohen
*	reviewer: Ben Ronen

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdlib.h> /* malloc, free*/
#include <assert.h> /* assert */

#include "../include/avl_tree.h"

/*Used in UpdateHeight function, to decide which subtree is higher*/
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/

enum successful {SUCCESS, FAILURE};
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~Declarations~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void SearchAndInsert(avl_t *tree, avl_node_t *node, void *data,
	 											avl_node_t *new_node);
static int UpdateHeight(avl_node_t *node);
static int PreorderForEach(avl_node_t *root, int (*action_t)(void *data,
                                            void *params), void *params);
static int InorderForEach(avl_node_t *root, int (*action_t)(void *data,
                                            void *params), void *params);
static int PostorderForEach(avl_node_t *root, int (*action_t)(void *data,
                                            void *params), void *params);
static avl_node_t *RecursiveFind(avl_t *tree, avl_node_t *node, void *key);
static int Counter(void *data, void *counter);
static void DestroyNode(avl_node_t *node);
static avl_node_t *SearchParent(avl_t *tree, avl_node_t *node,size_t *direction,
	 																void *data);
static avl_node_t *MinNode(avl_node_t *node);
static avl_node_t *NextNode(avl_node_t *node);
static avl_node_t *MaxNode(avl_node_t *node);
static avl_node_t *PrevNode(avl_node_t *node);
static int NumOfChildren(avl_node_t *node);
static int IsLeaf(avl_node_t *node);
static void FreeLeaf(avl_t *tree, avl_node_t *parent, int direction);
static void FreeNodeAndBypass(avl_t *tree, avl_node_t *parent, int direction,
	 											avl_node_t *node_to_remove);
static void SwapData(void **node_data, void **next_node_data);
static void FreeParentFor2Nodes(avl_t *tree, avl_node_t *node_to_remove);
static void RemoveRoot(avl_t *tree, avl_node_t *root);
static void UpdatePathHeightsAndBalance(avl_t *tree, avl_node_t *root,
	 												avl_node_t *node);
static int IsSameData(avl_t *tree, avl_node_t *node, const void *data);
static int GetNodeBalance(avl_node_t *node);
static avl_node_t *UpdateBalance(avl_t *tree, avl_node_t *node,
	 					avl_node_t *parent_node, size_t direction);
static void RotateRight(avl_node_t *node, avl_node_t *parent_node,
            						size_t direction, avl_t *tree);
static void RotateLeft(avl_node_t *node, avl_node_t *parent_node,
										size_t direction, avl_t *tree);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

avl_t *AVLCreate(is_before_t is_before)
{
    avl_t *tree = NULL;

    assert (NULL != is_before);

    tree = (avl_t *)malloc(sizeof(avl_t));
    if (NULL == tree)
    {
        return NULL;
    }

    tree->is_before = is_before;
    tree->root = NULL;

    return tree;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int AVLIsEmpty(const avl_t *tree)
{
    return (NULL == tree->root);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

size_t AVLSize(const avl_t *tree)
{
    int count = 0;

    assert(NULL != tree);

    AVLForEach((avl_t *)tree, Counter, &count, INORDER);

    return count;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int AVLHeight(const avl_t *tree)
{
	assert(NULL != tree);

    if (AVLIsEmpty(tree))
    {
        return -1;
    }

    return (tree->root->height);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int AVLForEach(avl_t *tree, int(*action_t)(void *data, void *params),
								void *params, traversal_t traversal)
{
	int status = SUCCESS;

    assert (NULL != tree);

    switch (traversal)
    {
        case PREORDER: status = PreorderForEach(tree->root, action_t, params);
                break;
        case INORDER: status = InorderForEach(tree->root, action_t, params);
                break;
        case POSTORDER: status = PostorderForEach(tree->root, action_t, params);
                break;
    }
	return status;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void AVLDestroy(avl_t *tree)
{
    assert(NULL != tree);

    DestroyNode(tree->root);

    free(tree);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int AVLInsert(avl_t *tree, const void *data)
{
    avl_node_t *new_node = NULL;

    assert(NULL != tree);
    assert (AVLFind(tree, data) == NULL);

    new_node = (avl_node_t *)malloc(sizeof(avl_node_t));
    if (NULL == new_node)
    {
        return FAILURE;
    }
    new_node->data = (void *)data;
    new_node->children[RIGHT] = NULL;
    new_node->children[LEFT] = NULL;
	new_node->height = 0;
    if (AVLIsEmpty(tree))
    {
        tree->root = new_node;
    }
    else
    {
        SearchAndInsert(tree, tree->root, (void *)data, new_node);
		UpdateBalance(tree, tree->root, NULL, LEFT);
	}


    return SUCCESS;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void *AVLFind(const avl_t *tree, const void *key)
{
	avl_node_t *key_node = tree->root;

	assert(NULL != tree);

	key_node = RecursiveFind((avl_t *)tree, key_node, (void *)key);
	if (NULL != key_node)
	{
		return key_node->data;
	}
	return NULL;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void *AVLRemove(avl_t *tree, const void *data)
{
	avl_node_t *parent;
	avl_node_t *node_to_remove;
	size_t direct = LEFT;
	size_t *direction = &direct;
	void *data_to_remove = NULL;

	assert(NULL != tree);

	data_to_remove = AVLFind(tree, data);
	if (NULL == data_to_remove)
	{
		return NULL;
	}

	if (IsSameData(tree, tree->root, data))
	{
		RemoveRoot(tree, tree->root);

		return data_to_remove;
	}

	parent = SearchParent(tree, tree->root, direction, (void *)data);
	node_to_remove = parent->children[*direction];

	switch (NumOfChildren(node_to_remove))
	{
		case 0: FreeLeaf(tree, parent, *direction);
				break;
		case 1: FreeNodeAndBypass(tree, parent, *direction, node_to_remove);
				break;
		case 2: FreeParentFor2Nodes(tree, node_to_remove);
				break;
	}

	UpdateBalance(tree, tree->root, NULL, LEFT);
    return data_to_remove;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Static Functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* auxiliary function for AVLInsert */
static void SearchAndInsert(avl_t *tree, avl_node_t *node, void *data,
	 											avl_node_t *new_node)
{
    size_t direction = tree->is_before(node->data, data);

    if (NULL == node->children[direction])
    {
		node->children[direction] = new_node;
		UpdateBalance(tree, node->children[direction], node, direction);
		UpdateHeight(node);

		return;
    }
    SearchAndInsert(tree, node->children[direction], data, new_node);
	UpdateHeight(node);

	UpdateBalance(tree, node->children[direction], node, direction);
	UpdateHeight(node);
}

/* auxiliary function for updating heights when return from each recursion.
 	uses - AVLInsert, AVLRemove */
static int UpdateHeight(avl_node_t *node)
{
    int right = -1;
    int left = -1;

    if(NULL != node->children[LEFT])
    {
        left = node->children[LEFT]->height;
    }
    if(NULL != node->children[RIGHT])
    {
        right = node->children[RIGHT]->height;
    }

    node->height = (MAX(left, right) + 1);

	return node->height;
}

/* auxiliary functions for AVLForEach */
static int PreorderForEach(avl_node_t *root, int (*action_t)(void *data,
                                            void *params), void *params)
{
    int status = SUCCESS;
    if (NULL == root)
    {
        return status;
    }
    status = action_t(root->data, params);
    PreorderForEach(root->children[LEFT], action_t, params);
    PreorderForEach(root->children[RIGHT], action_t, params);

    return status;
}

static int InorderForEach(avl_node_t *root, int (*action_t)(void *data,
                                            void *params), void *params)
{
    int status = SUCCESS;

    if (NULL == root)
    {
        return status;
    }
    InorderForEach(root->children[LEFT], action_t, params);
    status = action_t(root->data, params);
    InorderForEach(root->children[RIGHT], action_t, params);

    return status;
}

static int PostorderForEach(avl_node_t *root, int (*action_t)(void *data,
                                            void *params), void *params)
{
    int status = SUCCESS;

    if (NULL == root)
    {
        return status;
    }
    PostorderForEach(root->children[LEFT], action_t, params);
    PostorderForEach(root->children[RIGHT], action_t, params);
    status = action_t(root->data, params);

    return status;
}

/* action_func for AVLSize --> send as an argument to AVLForEach*/
static int Counter(void *data, void *counter)
{
    *(int *)counter += 1;

    (void)data;
    return *(int *)counter;
}

/* auxiliary function for AVLFind */
static avl_node_t *RecursiveFind(avl_t *tree, avl_node_t *node, void *key)
{
	size_t direction = LEFT;

	if (NULL == node)
	{ /* If arrive to the End of the list without Find */
		return NULL;
	}

	if (IsSameData(tree, node, key))
	{ /* Key Found ! */
		return node;
	}
	direction = tree->is_before(node->data, key);

	return RecursiveFind(tree, node->children[direction], key);
}

/* auxiliary function for AVLDestroy */
static void DestroyNode(avl_node_t *node)
{
    if (NULL == node)
    {
        return;
    }
    DestroyNode(node->children[LEFT]);
    DestroyNode(node->children[RIGHT]);
    free(node);

    return;
}

/*  return the parent of the node(which containing the data argument)
  	& update *direction from parent to the this node.
	uses - almost all over the code. */
static avl_node_t *SearchParent(avl_t *tree, avl_node_t *node,size_t *direction, void *data)
{
	*direction = tree->is_before(node->data, data);

	assert(NULL != node->children[*direction]);

	if (IsSameData(tree, node->children[*direction], data))
	{/* parent found ! */
		return node;
	}

	return SearchParent(tree, node->children[*direction], direction, data);
}

/* auxiliary function for NextNode */
static avl_node_t *MinNode(avl_node_t *node)
{
	if ((NULL == node->children[LEFT]))
	{
		return node;
	}

	return MinNode(node->children[LEFT]);
}

/* auxiliary function for PrevNode */
static avl_node_t *MaxNode(avl_node_t *node)
{
	if ((NULL == node->children[RIGHT]))
	{
		return node;
	} /* MinNode?*/
	return MaxNode(node->children[RIGHT]);
}

/* auxiliary function for "Remove issue"
   works only when there is children[LEFT]
   next = smallest node in the right branch  */
static avl_node_t *NextNode(avl_node_t *node)
{
	if (IsLeaf(node->children[RIGHT]))
	{
		return node->children[RIGHT];
	}
	return (MinNode(node->children[RIGHT]));
}

/* auxiliary function for RemoveRoot
   works only when there is children[LEFT] */
static avl_node_t *PrevNode(avl_node_t *node)
{
	if (IsLeaf(node->children[LEFT]))
	{
		return node->children[LEFT];
	}
	return (MaxNode(node->children[LEFT]));
}

/* return the number of children of the node */
static int NumOfChildren(avl_node_t *node)
{
    int count = 0;

    (NULL != (node->children[RIGHT]))? ++count:count;
    (NULL != (node->children[LEFT]))?  ++count:count;

    return count;
}

/* checks whether a node is a leaf or not? 1:0 */
static int IsLeaf(avl_node_t *node)
{
    return ((NULL == node->children[RIGHT])
        && (NULL == node->children[LEFT]));
}

/* auxiliary function for Remove a leaf node */
static void FreeLeaf(avl_t *tree, avl_node_t *parent, int direction)
{
    free(parent->children[direction]);
	parent->children[direction] = NULL;
	UpdatePathHeightsAndBalance(tree, tree->root, parent);
}

/* auxiliary function for Remove node with 2 children */
static void FreeNodeAndBypass(avl_t *tree, avl_node_t *parent, int direction,
	 								avl_node_t *node_to_remove)
{
	if (NULL != node_to_remove->children[LEFT])
	{/* case LEFT child exist */
		parent->children[direction] = node_to_remove->children[LEFT];
	}
	else /* (NULL != node_to_remove->children[RIGHT]) */
	{
		parent->children[direction] = node_to_remove->children[RIGHT];
	}

	free(node_to_remove); node_to_remove = NULL;
	UpdatePathHeightsAndBalance(tree, tree->root, parent);
}

/* auxiliary function for FreeParentFor2Nodes */
static void SwapData(void **node_data, void **next_node_data)
{
	void *tmp = *node_data;
	*node_data = *next_node_data;
	*next_node_data = tmp;
}

/* auxiliary function for Remove node with 2 children */
static void FreeParentFor2Nodes(avl_t *tree,avl_node_t *node_to_remove)
{
	avl_node_t *next_node = NULL;
	avl_node_t *parent_of_next = NULL;
	size_t direction = 777;

	next_node = NextNode(node_to_remove);
	parent_of_next = SearchParent(tree, tree->root, &direction, next_node->data);
	SwapData(&node_to_remove->data, &next_node->data);

	switch (NumOfChildren(next_node))
	{
		case 0: FreeLeaf(tree, parent_of_next, direction);
				break;
		case 1: FreeNodeAndBypass(tree, parent_of_next, direction, next_node);
				break;
	}
	UpdatePathHeightsAndBalance(tree, tree->root, parent_of_next);
}

/* Swap root with one of his children and remove the child */
static void RemoveRoot(avl_t *tree, avl_node_t *root)
{
	size_t direction = 777;

	if (NULL != root->children[RIGHT])
	{/* if there is RIGHT child */
		avl_node_t *next_root = NextNode(root);
		avl_node_t *parent_of_next = SearchParent(tree, root, &direction, next_root->data);
		SwapData(&root->data, &next_root->data);

		switch (NumOfChildren(next_root))
		{
			case 0: FreeLeaf(tree, parent_of_next, direction);
					break;
			case 1: FreeNodeAndBypass(tree, parent_of_next, direction, next_root);
					break;
			case 2: FreeParentFor2Nodes(tree, next_root);
					break;
		}
	}
	else if (NULL == root->children[RIGHT] && NULL != root->children[LEFT])
	{/* if there is *only* LEFT child */
		avl_node_t *prev_root = PrevNode(root);
		avl_node_t *parent_of_prev = SearchParent(tree, root, &direction, prev_root->data);
		SwapData(&root->data, &prev_root->data);

		switch (NumOfChildren(prev_root))
		{
			case 0: FreeLeaf(tree, parent_of_prev, direction);
					break;
			case 1: FreeNodeAndBypass(tree, parent_of_prev, direction, prev_root);
					break;
			case 2: FreeParentFor2Nodes(tree, prev_root);
					break;
		}
	}
	else /* root have no children */
	{
		free (tree->root);
		tree->root = NULL;
	}
}

/* run recursivly from root to the wanted node
   because AVLRemove isn't recursice func this func runs seperately */
static void UpdatePathHeightsAndBalance(avl_t *tree, avl_node_t *root, avl_node_t *node)
{
	size_t direction = tree->is_before(root->data, node->data);

	if (NULL == root->children[direction])
	{
		UpdateHeight(root);
		/* Last UpdateBalance(root rebalance) is in the end og AVLRemove func */
		return;
	}
	UpdatePathHeightsAndBalance(tree, root->children[direction], node);
	UpdateHeight(root);
	UpdateBalance(tree, root->children[direction], root, direction);
}

/* auxiliary function to check if (node->data == data) ? */
static int IsSameData(avl_t *tree, avl_node_t *node, const void *data)
{
	return ((tree->is_before(node->data, data) ==
			tree->is_before(data, node->data)));
}

/* auxiliary function to Calculate node balance
   useses - after return from recursion in removal/insertion */
static int GetNodeBalance(avl_node_t *node)
{
	int right_child_height = -1;
	int left_child_height = -1;

	assert (NULL != node);

	if (NULL != node->children[LEFT])
	{
		left_child_height = node->children[LEFT]->height;
	}
	if (NULL !=  node->children[RIGHT])
	{
		right_child_height = node->children[RIGHT]->height;
	}

	return left_child_height - right_child_height;
}

/* auxiliary function for UpdateBalance */
static void RotateRight(avl_node_t *node, avl_node_t *parent_node,
            						size_t direction, avl_t *tree)
{
    avl_node_t *tmp = node->children[LEFT];

    node->children[LEFT] = tmp->children[RIGHT];
    tmp->children[RIGHT] = node;
    if (NULL != parent_node)
    {
        parent_node->children[direction] = tmp;
    }
    else
    {/* if node is root so - there is no parent_node to update*/
        tree->root = tmp;
    }
    node->height = UpdateHeight(node);
    tmp->height = UpdateHeight(tmp);
}

/* auxiliary function for UpdateBalance */
static void RotateLeft(avl_node_t *node, avl_node_t *parent_node,
            						size_t direction, avl_t *tree)
{
    avl_node_t *tmp = node->children[RIGHT];

    node->children[RIGHT] = tmp->children[LEFT];
    tmp->children[LEFT] = node;
    if (NULL != parent_node)
    {
        parent_node->children[direction] = tmp;
    }
    else
    {/* if node is root so - there is no parent node to update*/
        tree->root = tmp;
    }
    node->height = UpdateHeight(node);
    tmp->height = UpdateHeight(tmp);
}

/* auxiliary function to Rebalance the tree after insertion/removal
when |balance factor| grows and get bigger than 1. if(|BF| > 1) */
static avl_node_t *UpdateBalance(avl_t *tree, avl_node_t *node,
	 					avl_node_t *parent_node, size_t direction)
{
	if (GetNodeBalance(node) > 1)
    {
        if (GetNodeBalance(node->children[LEFT]) < 0)
        {
            RotateLeft(node->children[LEFT], node, LEFT, tree);
        }
        RotateRight(node, parent_node, direction, tree);
    }
    else if (GetNodeBalance(node) < -1)
    {
        if (GetNodeBalance(node->children[RIGHT]) > 0)
        {
            RotateRight(node->children[RIGHT], node, RIGHT, tree);
        }
        RotateLeft(node, parent_node, direction, tree);
    }

	return node;
}
