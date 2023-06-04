/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: binary_sorted_tree.c
*	author: Moshe Cohen
*	reviewer: Roy

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "binary_sorted_tree.h"
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/

enum child_size_t {LEFT, RIGHT, NUM_OF_CHILDREN};
enum status_t {SUCCESS, FAILURE};
enum matching_t {NO, YES};

typedef struct node
{
	void *data;
	struct node *parent;
	struct node *children[NUM_OF_CHILDREN];
} bst_node_t;

struct binary_sorted_tree
{
	bst_node_t stub; /* root */
	is_before_t is_before;
};
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~helper functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static int IsLeaf(bst_iter_t iter);
static int NumOfChildren(bst_iter_t iter);
static void FreeLeaf(bst_iter_t leaf);
static void BypassIter(bst_iter_t iter);
static void FreeDaddyFor2(bst_iter_t iter);
static bst_iter_t MinIter(bst_node_t *iter);
static bst_iter_t MaxIter(bst_node_t *iter);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

bst_t *BSTCreate(is_before_t is_before)
{
    bst_t *tree = NULL;

    assert (NULL != is_before);

    tree = (bst_t *)malloc(sizeof(bst_t));
    if (NULL == tree)
    {
        printf("allocation FAILURE\n");
        return NULL;
    }

    tree->stub.data = NULL;
    tree->stub.parent = NULL;
    tree->stub.children[RIGHT] = NULL;
    tree->stub.children[LEFT] = NULL;

    tree->is_before = is_before;

    return tree;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void BSTDestroy(bst_t *tree)
{

    bst_node_t *iter = NULL;
	bst_node_t *parent = NULL;
	bst_node_t *root = NULL;

    assert (NULL != tree);

	root = &tree->stub;
	iter = root->children[LEFT];

	/* Remove node by node according post-order traversal - LRN */
	while (NO == BSTIsEmpty(tree))
	{
		/* L */
		if (NULL != iter->children[LEFT])
		{
			parent = iter;
			iter = iter->children[LEFT];
			continue;
		}
		/* R */
		else if (NULL != iter->children[RIGHT])
		{
			parent = iter;
			iter = iter->children[RIGHT];
			continue;
		}
		/* N */
		else
		{
			FreeLeaf(iter);
			if (NULL != parent)
			{
				iter = parent;
				parent = iter->parent;
			}
		}
	}

    free(tree); tree = NULL;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

size_t BSTSize(const bst_t *tree)
{
    size_t count = 0;
    bst_node_t *runner = BSTBegin(tree);

    assert (NULL != tree);

    while (NO == BSTIsSameIter(runner, BSTEnd(tree)))
    {
        runner = BSTNext(runner);
        ++count;
    }

    return count;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int BSTIsEmpty(const bst_t *tree)
{
    assert (NULL != tree);

    return (NULL == tree->stub.children[LEFT]);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

bst_iter_t BSTInsert(bst_t *tree, const void *data)
{
    bst_node_t *node = NULL;
    bst_node_t *current = NULL;
    int side = LEFT;

    assert (NULL != tree);
    assert (BSTFind(tree, data) == BSTEnd(tree));

    node = (bst_node_t *)malloc(sizeof(bst_node_t));
    if (NULL == node)
    {
        printf("allocation FAILURE\n");
        return BSTEnd(tree);
    }
    node->data = (void *)data;
    node->children[RIGHT] = NULL;
    node->children[LEFT] = NULL;

    for (current = &tree->stub, side = LEFT; NULL != current->children[side];
        side = (*tree->is_before)(current->data, data))
    {
        current = current->children[side];
    }
    current->children[side] = node;
    node->parent = current;

    return node;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void BSTRemove(bst_iter_t iter)
{
    assert (NULL != iter);

    switch (NumOfChildren(iter))
    {
        case 0: FreeLeaf(iter);
                break;
        case 1: BypassIter(iter);
                break;
        case 2: FreeDaddyFor2(iter);
                break;
    }
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

bst_iter_t BSTBegin(const bst_t *tree)
{
    bst_node_t *runner = NULL;

    assert (NULL != tree);

    runner = &((bst_t *)(tree))->stub;
    while (NULL != runner->children[LEFT])
    {
        runner = runner->children[LEFT];
    }

    return (bst_iter_t)runner;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

bst_iter_t BSTEnd(const bst_t *tree)
{
    bst_node_t *end = NULL;

    assert (NULL != tree);

    end = &((bst_t *)(tree))->stub;

    return (end);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* return the successor iter of iter */
bst_iter_t BSTNext(bst_iter_t iter)
{
    bst_node_t *iterator = ((bst_node_t *)iter);
    bst_node_t *parent_runner = iterator->parent;

    /* right branch is exist */
    if (NULL != iterator->children[RIGHT])
    {
        return (MinIter(iterator->children[RIGHT]));
    }
    /* if there is NOT right branch */
    while (NULL != parent_runner && iterator == parent_runner-> children[RIGHT])
    {
        iterator = parent_runner;
        parent_runner = parent_runner->parent;
    }

    return (bst_iter_t)parent_runner;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void *BSTGetData(bst_iter_t iter)
{
    assert (NULL != iter);

    return (((bst_node_t *)iter)->data);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

bst_iter_t BSTPrev(bst_iter_t iter)
{

    bst_node_t *iterator = ((bst_node_t *)iter);
    bst_node_t *parent_runner = iterator->parent;

    assert (NULL != iter);

    /* LEFT branch is exist */
    if (NULL != iterator->children[LEFT])
    {
        return (MaxIter(iterator->children[LEFT]));
    }
    /* if there is NOT children[LEFT] */
    while (NULL != parent_runner && iterator == parent_runner-> children[LEFT])
    {
        iterator = parent_runner;
        parent_runner = parent_runner->parent;
    }

    return (bst_iter_t)parent_runner;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int BSTIsSameIter(bst_iter_t lhs, bst_iter_t rhs)
{
    assert (NULL != lhs);
    assert (NULL != rhs);

    return (lhs == rhs);

}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

bst_iter_t BSTFind(const bst_t *tree, const void *data)
{
    bst_node_t *current = NULL;
    int side = LEFT;

    assert (NULL != tree);

    current = BSTEnd(tree); /*&((bst_t *)tree)->stub*/
    while (NULL != current->children[side])
    {
        current = current->children[side];
        if (tree->is_before(current->data, data) ==
                tree->is_before(data, current->data))
        {
            return current;
        }
        side = tree->is_before(current->data, data);
    }

    return BSTEnd(tree);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int BSTForEach(bst_t *tree, int (*action_t)(void *data, void *params),
								                         void *params)
{
    bst_node_t *runner = NULL;
    short status = SUCCESS;

    assert (NULL != action_t);
    assert (NULL != tree);

    runner = BSTBegin(tree);

    while (BSTEnd(tree) != runner)
    {
        status = action_t(BSTGetData(runner), params);
        runner = BSTNext(runner);
    }

    return status;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~helper functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static int IsLeaf(bst_iter_t iter)
{
    return ((NULL == ((bst_node_t *)iter)->children[RIGHT])
        && (NULL == ((bst_node_t *)iter)->children[LEFT]));
}

static int NumOfChildren(bst_iter_t iter)
{
    int count = 0;

    (NULL != ((bst_node_t *)iter)->children[RIGHT])? ++count:count;
    (NULL != ((bst_node_t *)iter)->children[LEFT])?  ++count:count;

    return count;
}

static void FreeLeaf(bst_iter_t leaf)
{
    bst_node_t *iter = (bst_node_t *)leaf;
    int side = (iter->parent->children[RIGHT] == iter);

    iter->parent->children[side] = NULL;

    free(leaf); iter = NULL; leaf = NULL;
}

/* Bypass & Remove Iter with 1 child */
static void BypassIter(bst_iter_t iter)
{
    bst_node_t *iterator = ((bst_node_t *)iter);
    int side = (iterator->parent->children[RIGHT] == iterator);

    if (NULL != iterator->children[LEFT])
    { /* case LEFT child exist */
        iterator->children[LEFT]->parent = iterator->parent;
        iterator->parent->children[side] = iterator->children[LEFT];
    }
    else /* (NULL != iter->children[RIGHT])*/
    {
        iterator->children[RIGHT]->parent = iterator->parent;
        iterator->parent->children[side] = iterator->children[RIGHT];
    }

    free(iter); iter = NULL;
}

/* return the minimum(LEFAT) iter in the subtree - iter is his root*/
static bst_iter_t MinIter(bst_node_t *iter)
{
    bst_node_t *iterator = ((bst_node_t *)iter);

    while (NULL != iterator->children[LEFT])
    {
        iterator = iterator->children[LEFT];
    }

    return (bst_iter_t)iterator;
}

/* return the maximum iter(RIGHT) in the subtree - iter is his root*/
static bst_iter_t MaxIter(bst_node_t *iter)
{
    bst_node_t *iterator = ((bst_node_t *)iter);

    while (NULL != iterator->children[RIGHT])
    {
        iterator = iterator->children[RIGHT];
    }

    return (bst_iter_t)iterator;
}

/* Free node with 2 children */
static void FreeDaddyFor2(bst_iter_t iter)
{
    bst_node_t *n_free = (bst_node_t *)iter;

    for(; NO == IsLeaf(n_free); n_free = BSTNext(n_free))
    {
      n_free->data = ((bst_node_t *)BSTNext(n_free))->data;
    }

    FreeLeaf(n_free);
}
