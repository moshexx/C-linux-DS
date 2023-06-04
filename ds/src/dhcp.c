/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: dhcp.c
*	author: Moshe Cohen
*	reviewer: Lidor Cohen

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert */
#include <math.h> 	/* pow() */
#include <string.h> /* memset() */

#include "dhcp.h"

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define NUM_OF_CHILDREN 2
#define BITS_IN_BYTE 8
#define TOTAL_BITS (IP_SIZE) * (BITS_IN_BYTE)  /* 32 = 4 Bytes * 8 bits for each Byte */
#define NUM_OF_BITS_IN_HOST (TOTAL_BITS - dhcp->num_of_bits_in_subnet)

typedef struct trie trie_t;

typedef struct node node_t;

struct node
{
	node_t *children[NUM_OF_CHILDREN];
	int is_full;
};

struct dhcp
{
    trie_t *trie;
    ipv4_t subnet_ip;
    size_t num_of_bits_in_subnet;
};

struct trie
{
	node_t *root;
};
/*~~~~~~~~~~~~~~~~~~~~~~~~ helper functions ddeclarations ~~~~~~~~~~~~~~~~~~~~~*/

static void DestroyTrie(node_t *root_node);
static dhcp_t *AllocReservedIPs(dhcp_t *dhcp);
static node_t *CreateNode(node_t *node, int state);
static void SetBitState(unsigned char *arr, size_t index, int state);
static int GetBitState(unsigned char *ip, size_t index);
static dhcp_status_t Insert(dhcp_t *dhcp, node_t *node, size_t index,
	 			 				ipv4_t requested_ip, ipv4_t *_result);
static void Free(dhcp_t *dhcp,  node_t *node, size_t index, ipv4_t ip_to_free);
static void CountLeaf(node_t *node, size_t *count);
static dhcp_status_t CreateRightChildIfNeeded(node_t *node);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ API functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

dhcp_t *DhcpCreate(ipv4_t subnet_ip, size_t num_of_bits_in_subnet)
{
	trie_t *trie = NULL;
	dhcp_t *dhcp = NULL;
	node_t *root = NULL;

	root = (node_t *)malloc(sizeof(node_t));
	if (NULL == root)
	{
		return NULL;
	}
	trie = (trie_t *)malloc(sizeof(trie_t));
	if (NULL == trie)
	{
		free(root); root = NULL;
		return NULL;
	}
	dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
	if (NULL == dhcp)
	{
		free(root); root = NULL;
		free(trie); trie = NULL;
		return NULL;
	}
	root->is_full = 0;
	root->children[0] = NULL;
	root->children[1] = NULL;
	trie->root = root;
	dhcp->trie = trie;
	dhcp->subnet_ip = subnet_ip;
	dhcp->num_of_bits_in_subnet = num_of_bits_in_subnet;

	if (NULL == AllocReservedIPs(dhcp))
	{
		DhcpDestroy(dhcp);
		return NULL;
	}

	return dhcp;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void DhcpDestroy(dhcp_t *dhcp)
{
    assert(NULL != dhcp);

	DestroyTrie(dhcp->trie->root);

    free(dhcp->trie); dhcp->trie = NULL;
	free(dhcp); dhcp = NULL;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

dhcp_status_t DhcpAllocateIp(dhcp_t *dhcp, ipv4_t requested_ip, ipv4_t *_result)
{
	size_t index = 0;
	dhcp_status_t status = SUCCESS;

	assert(NULL != dhcp);

	index = NUM_OF_BITS_IN_HOST - 1;
	if (1 == dhcp->trie->root->is_full)
	{
		memset(_result->ip, 0, 4);
		return FULL;
	}
	*_result = dhcp->subnet_ip;
	status = Insert(dhcp, dhcp->trie->root, index, requested_ip, _result);

	return status;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void DhcpFreeIp(dhcp_t *dhcp, ipv4_t ip_to_free)
{
	size_t index = 0;

    assert(NULL != dhcp);

	index = NUM_OF_BITS_IN_HOST - 1;

	Free(dhcp, dhcp->trie->root, index, ip_to_free);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

size_t DhcpCountFree(const dhcp_t *dhcp)
{
	size_t count = 0;

    assert(NULL != dhcp);

	CountLeaf(dhcp->trie->root, &count);

    return (pow(2, NUM_OF_BITS_IN_HOST) - count);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ helper functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* auxiliary function for DhcpDestroy */
static void DestroyTrie(node_t *root_node)
{
    if (NULL == root_node)
    {
        return;
    }
    DestroyTrie(root_node->children[0]);
    DestroyTrie(root_node->children[1]);
    free(root_node);

    return;
}

/* auxiliary function for DhcpCreate */
static dhcp_t *AllocReservedIPs(dhcp_t *dhcp)
{
	dhcp_status_t status = SUCCESS;
	ipv4_t broadcast_address = {{255, 255, 255, 255}};
	ipv4_t server_address = {{255, 255, 255, 254}};
	ipv4_t network_address = {{0, 0, 0, 0}};

	ipv4_t broadcast_ip = {{0}};
	ipv4_t server_ip = {{0}};
	ipv4_t network_ip = {{0}};

	status = DhcpAllocateIp(dhcp, broadcast_address, &broadcast_ip);
	if (status != SUCCESS)
	{
		return NULL;
	}
	status = DhcpAllocateIp(dhcp, server_address, &server_ip);
	if (status != SUCCESS)
	{
		return NULL;
	}
	status = DhcpAllocateIp(dhcp, network_address, &network_ip);
	if (status != SUCCESS)
	{
		return NULL;
	}

	return dhcp;
}

static node_t *CreateNode(node_t *node, int state)
{
	node->children[state] = (node_t *)malloc(sizeof(node_t));
	if (NULL == node->children[state])
	{
		return NULL;
	}
	node->children[state]->children[0] = NULL;
	node->children[state]->children[1] = NULL;
	node->children[state]->is_full = 0;

	return node->children[state];
}

/* Update _result */
static void SetBitState(unsigned char *arr, size_t index, int state)
{
    /*find right elem in the array to which index belongs*/
    size_t current_byte = IP_SIZE - 1 - (index / BITS_IN_BYTE);
    /*normalize general index to in-char index i*/
    size_t i = (index % BITS_IN_BYTE);

    arr[current_byte] = (arr[current_byte] ^ (arr[current_byte] & (1 << i)))
                		| ((unsigned char)state << i);
}

static int GetBitState(unsigned char *ip, size_t index)
{
	size_t current_byte = IP_SIZE - 1 - (index / BITS_IN_BYTE);
	size_t index_real = index % BITS_IN_BYTE;
	unsigned char mask = 1 << index_real;

	return (0 != (ip[current_byte] & mask));
}

static dhcp_status_t Insert(dhcp_t *dhcp, node_t *node, size_t index,
	 			 				ipv4_t requested_ip, ipv4_t *_result)
{
	size_t state = GetBitState(requested_ip.ip, index);
	dhcp_status_t status = SUCCESS;

	/* base case */
	if (1 == node->is_full)
	{
		return FULL;
	}
	if (0 == index)
	{
		if (NULL == node->children[state])
		{
			node->children[state] = CreateNode(node, state);
			if (NULL == node->children[state])
			{
				return ALLOCATION_FAILURE;
			}
			node->children[state]->is_full = 1;

			node->is_full = (node->children[!state] != NULL);
			SetBitState(_result->ip, index, state);

			return SUCCESS;
		}
		else if (0 == state && NULL == node->children[1])
		{
			node->children[1] = CreateNode(node, 1);
			node->is_full = 1;
			SetBitState(_result->ip, index, 1);

			return REPLACED;
		}
		else /*(1 == node->children[state]->is_full)*/
		{
			return FULL;
		}
	}

	/************* body of function & recurstion *************/
	if (NULL == node->children[state])
	{
		node->children[state] = CreateNode(node, state);
		if (NULL == node->children[state])
		{
			return ALLOCATION_FAILURE;
		}
	}

	status = Insert(dhcp, node->children[state], index - 1, requested_ip, _result);

	/************* after returning from recurstion *************/
	if (FULL == status && 0 == state)
	{
		ipv4_t next_ip = {{0}};

		if (ALLOCATION_FAILURE == CreateRightChildIfNeeded(node))
		{
			return ALLOCATION_FAILURE;
		}

		if (0 == node->children[1]->is_full)
		{
			state = 1;
			status = Insert(dhcp, node->children[1], index - 1, next_ip, _result);
			status == SUCCESS? status = REPLACED : status;
		}
	}

	/* Update parent fullness */
	if (NULL != node->children[0] && 1 == node->children[0]->is_full
		&& NULL != node->children[1] && 1 == node->children[1]->is_full)
	{
		node->is_full = 1;
	}
	SetBitState(_result->ip, index, state);

	return status;
}

static void Free(dhcp_t *dhcp,  node_t *node, size_t index, ipv4_t ip_to_free)
{
	size_t state = GetBitState(ip_to_free.ip, index);

	/* Base Case  - last index to check */
	if (0 == index)
	{
		free(node->children[state]); node->children[state] = NULL;
		node->is_full = 0;
	}
	/* if the ip_to_free or some node from his path isn't existing */
	if (NULL == node->children[state])
	{
		return;
	}

	Free(dhcp, node->children[state], index - 1, ip_to_free);
	if (NULL == node->children[state]->children[0] &&
		 	NULL == node->children[state]->children[1])
	{
		free(node->children[state]);
		node->children[state] = NULL;
	}
	node->is_full = 0;
}

static void CountLeaf(node_t *node, size_t *count)
{
	if (NULL == node->children[0] && NULL == node->children[1])
	{
		*count += 1;
		return;
	}

	if (node->children[0] != NULL)
	{
		CountLeaf(node->children[0], count);
	}
	if (node->children[1] != NULL)
	{
		CountLeaf(node->children[1], count);
	}
}

static dhcp_status_t CreateRightChildIfNeeded(node_t *node)
{
	if((NULL == node->children[1]))
	{
		node->children[1] = CreateNode(node, 1);
		if (NULL == node->children[1])
		{
		   return ALLOCATION_FAILURE;
		}
		node->children[1]->is_full = 0;
	}

	return SUCCESS;
}
