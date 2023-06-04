/*******************************************************************************
*		Descriptions - DHCP API Functions V2	                                   *
*		Date: 17.12.2020						                               *
*		Group: OL96							                                   *
*******************************************************************************/

#ifndef __DHCP_H__
#define __DHCP_H__
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stddef.h> /* size_t */

#define IP_SIZE 4

typedef struct dhcp dhcp_t;
typedef enum
{
	SUCCESS,
	REPLACED,
    FULL,
    ALLOCATION_FAILURE
}dhcp_status_t;

typedef struct ip_address
{
     unsigned char ip[IP_SIZE];
}ipv4_t;


/* in src file


#define NUM_OF_CHILDREN 2

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

end of src file */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*
* Description: Create dhcp.
* Return value: Pointer of dhcp.
* Errors: Return NULL when fail allocate memory.
* Undefined behavior:
* Complexity: O(nlog n).
*/
dhcp_t *DhcpCreate(ipv4_t subnet_ip, size_t num_of_bits_in_subnet);

/*
* Description: free the dhcp.
* Return value: none.
* Errors: None
* Undefined behavior: @dhcp is NULL.
*
* Complexity: O(nlog n).
*/
void DhcpDestroy(dhcp_t *dhcp);

/*
* Description: allocate available ip address, if requested address not
                            available, closest higher address will be returned,
                            the address will be returned in @_result pointer.
* Return value: SUCCESS when ip address is available,
                REPLACED when returned different address than requested,
                FULL when no address is available,
                ALLOCATION_FAILURE when allocation failed.
* Errors: ALLocation failure.
* Undefined behavior: @dhcp is NULL, @requested_ip illegal.
*
* Complexity: O(log(n))
*/
dhcp_status_t DhcpAllocateIp(dhcp_t *dhcp, ipv4_t requested_ip, ipv4_t *_result);

/*
* Description: free the @ip_to_free address
* Return value: none.
* Errors: none.
* Undefined behavior: @dhcp is NULL, @ip_to_free illegal.
*
* Complexity: O(log(n))
*/
void DhcpFreeIp(dhcp_t *dhcp, ipv4_t ip_to_free);

/*
* Description: count the number of free addresses.
* Return value: number of free addresses.
* Errors: none.
* Undefined behavior: @dhcp is NULL.
*
* Complexity: O(nlog(n)).
*/
size_t DhcpCountFree(const dhcp_t *dhcp);



#endif   /*__DHCP_H___*/
