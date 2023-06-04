/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_dhcp.c
*	author: Nir Shaulian
*	reviewer:

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> /*printf */
#include <string.h> /* memcmp */
#include <math.h> /* pow */
#include <limits.h> /* CHAR_BIT */

#include "dhcp.h"

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define RED printf("\033[0;31m")
#define GREEN printf("\033[0;32m")
#define YELLOW printf("\033[01;33m")
#define BLUE printf("\033[0;34m")
#define BLUE_BOLD printf("\033[01;34m")

#define RESET printf("\033[0m")
#define RUN_TEST(result, name) {\
            printf("Test %s: ", name);\
            if (result)\
            {\
                GREEN;\
                printf("Success\n");\
                RESET;\
            }\
            else\
            {\
                RED;\
                printf("Failed\n");\
                RESET;\
            }\
        }
#define SUBNET_TEST_SIZE 17
#define IP_BITS IP_SIZE * CHAR_BIT


enum matching_t
{
	NO,
	YES
};
/*~~~~~~~~~~~~~~~~~~~~~~~~~static funcs declerations ~~~~~~~~~~~~~~~~~~~~~~~~*/
static int TestCreate();
static int TestAlloc();
static int TestFree(void);
static int TestAllocAdvanced();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ main ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int main()
{

    YELLOW;
    printf("    Test Begin now\n");
    RESET;


    TestCreate();
    TestAlloc();
    TestFree();
    TestAllocAdvanced();


	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~staic funcs definitions~~~~~~~~~~~~~~~~~~~~~~~~~*/
static int TestFree(void)
{
    dhcp_t *dhcp = NULL;
    ipv4_t subnet_ip = {{1, 1, 1, 1}};
    ipv4_t result = {{0}};

    BLUE_BOLD;
    printf("    Test Free\n");
    RESET;

    dhcp = DhcpCreate(subnet_ip, 24);
    if (dhcp == NULL)
    {
        printf("Create Allocation failed!\n");
        return 1;
    }

    if(ALLOCATION_FAILURE == DhcpAllocateIp(dhcp, subnet_ip, &result))
    {
        return 1;
    }
    DhcpFreeIp(dhcp, subnet_ip);

    RUN_TEST(253 == DhcpCountFree(dhcp), "Free & Count Free");
    RUN_TEST(SUCCESS == DhcpAllocateIp(dhcp, subnet_ip, &result),
                                                    "Free (alloc after free)");
    DhcpDestroy(dhcp);

    return SUCCESS;
}

static int TestAllocAdvanced()
{
    dhcp_t *dhcp = NULL;
    ipv4_t subnet_ip = {{1, 1, 1, 1}};
    ipv4_t result = {{0}};
    ipv4_t test = {{0, 0, 0, 3}};
    char ch_arr[IP_SIZE] = {1, 1, 1, 1};
    size_t i = 0;
    dhcp_status_t status = REPLACED;

    BLUE_BOLD;
    printf("    Test Allocate Advanced\n");
    RESET;

    dhcp = DhcpCreate(subnet_ip, 23);
    if (dhcp == NULL)
    {
        printf("Create Allocation failed!\n");
        return 1;
    }

    RUN_TEST(SUCCESS == DhcpAllocateIp(dhcp, subnet_ip, &result),
                                                        "Allocate address 1");
    RUN_TEST(508 == DhcpCountFree(dhcp), "Allocate & Count Free");
    RUN_TEST(0 == memcmp(ch_arr, result.ip, IP_SIZE), "Allocate & memcmp");

    RUN_TEST(SUCCESS == DhcpAllocateIp(dhcp, test, &result),
                                            "Allocate 2");
    RUN_TEST(507 == DhcpCountFree(dhcp), "Allocate & Count Free");

    subnet_ip.ip[2] = 0;
    subnet_ip.ip[3] = 3;
    RUN_TEST(0 == memcmp(subnet_ip.ip, result.ip, IP_SIZE), "Allocate & memcmp");

    RUN_TEST(REPLACED == DhcpAllocateIp(dhcp, test, &result),
                                            "Allocate 3 (same address again)");
    RUN_TEST(506 == DhcpCountFree(dhcp), "Allocate & Count Free");
    subnet_ip.ip[2] = 0;
    subnet_ip.ip[3] = 4;
    RUN_TEST(0 == memcmp(subnet_ip.ip, result.ip, IP_SIZE), "Allocate & memcmp");

    for (i = 4; i < 256; ++i)
    {
        if(ALLOCATION_FAILURE == DhcpAllocateIp(dhcp, subnet_ip, &result))
        {
            printf("Allocate failed in line %d\n", __LINE__);
            return 1;
        }
    }
    subnet_ip.ip[2] = 1;
    subnet_ip.ip[3] = 0;
    RUN_TEST(0 == memcmp(subnet_ip.ip, result.ip, IP_SIZE), "Allocate & memcmp");

    DhcpDestroy(dhcp); dhcp = NULL;

    test.ip[0] = 0;
    test.ip[1] = 0;
    test.ip[2] = 0;
    test.ip[3] = 0;
    dhcp = DhcpCreate(subnet_ip, SUBNET_TEST_SIZE);
    if (dhcp == NULL)
    {
        printf("Create Allocation failed!\n");
        return 1;
    }

    status = REPLACED;
    for (i = 0; i < (pow(2,  32 - SUBNET_TEST_SIZE) - 3) &&
                                        REPLACED == status; ++i)
    {
        status = DhcpAllocateIp(dhcp, test, &result);
        if(ALLOCATION_FAILURE == status)
        {
            printf("Allocate failed in line %d\n", __LINE__);
            return 1;
        }
    }
    RUN_TEST(pow(2,  32 - SUBNET_TEST_SIZE) - 3 == i, "Allocate all addresses");
    RUN_TEST(0 == DhcpCountFree(dhcp), "Allocate all & Count Free");
    RUN_TEST(FULL == DhcpAllocateIp(dhcp, test, &result),
                                    "alloc When all addresses are allocated");

    DhcpDestroy(dhcp); dhcp = NULL;

    return SUCCESS;
}

static int TestAlloc()
{
    dhcp_t *dhcp = NULL;
    ipv4_t subnet_ip = {{1, 1, 1, 1}};
    ipv4_t result = {{0}};
    char ch_arr[IP_SIZE] = {1, 1, 1, 1};

    BLUE_BOLD;
    printf("    Test Allocate\n");
    RESET;

    dhcp = DhcpCreate(subnet_ip, 24);
    if (dhcp == NULL)
    {
        printf("Create Allocation failed!\n");
        return 1;
    }
    RUN_TEST(SUCCESS == DhcpAllocateIp(dhcp, subnet_ip, &result),
                                                        "Allocate address 1");
    RUN_TEST(252 == DhcpCountFree(dhcp), "Allocate & Count Free");
    RUN_TEST(0 == memcmp(ch_arr, result.ip, IP_SIZE), "Allocate & memcmp");

    RUN_TEST(REPLACED == DhcpAllocateIp(dhcp, subnet_ip, &result),
                                            "Allocate 2 (same address again)");
    RUN_TEST(251 == DhcpCountFree(dhcp), "Allocate & Count Free");
    ch_arr[IP_SIZE -1] = 2;
    RUN_TEST(0 == memcmp(ch_arr, result.ip, IP_SIZE), "Allocate & memcmp");

    subnet_ip.ip[IP_SIZE - 1] = 255;
    RUN_TEST(FULL == DhcpAllocateIp(dhcp, subnet_ip, &result),
                                            "Allocate 3 (server ip)");
    RUN_TEST(251 == DhcpCountFree(dhcp), "Allocate & Count Free");




    DhcpDestroy(dhcp);

    return SUCCESS;
}

static int TestCreate()
{
    dhcp_t *dhcp = NULL;
    ipv4_t subnet_ip = {{1, 1, 1, 1}};

    BLUE_BOLD;
    printf("    Test Create\n");
    RESET;

    dhcp = DhcpCreate(subnet_ip, 24);
    if (dhcp == NULL)
    {
        printf("Create Allocation failed!\n");
        return 1;
    }
    RUN_TEST(253 == DhcpCountFree(dhcp), "Create & Count Free");

    DhcpDestroy(dhcp);

    return SUCCESS;
}
