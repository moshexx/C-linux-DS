/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_dhcp.c
*	author: Moshe Cohen
*	reviewer: Lidor Cohen

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> /* printf */
#include <stdlib.h> /* memcmp */
#include <string.h>

#include "../include/dhcp.h"

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define RED printf("\033[0;31m")
#define GREEN printf("\033[0;32m")
#define YELLOW printf("\033[01;33m")
#define BLUE printf("\033[0;34m")
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

/*enum successful {SUCCESS, FAILURE};*/
enum matching {NO, YES};
#define SIZE 254
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int BasicTest(void);
void PrintIP4(ipv4_t ip);
int main()
{
    BasicTest();

	return 0;
}

int BasicTest(void)
{
    ipv4_t net = {{255,255,255,0}};
    ipv4_t ip1[SIZE];
    size_t i;
    dhcp_t *dhcp;
    ipv4_t res;

    dhcp = DhcpCreate(net, 24);
    printf("\nDhcpAllocateIp\n");
    for (i = 1; i < SIZE; ++i)
    {
        ip1[i].ip[0] = 255;
        ip1[i].ip[1] = 255;
        ip1[i].ip[2] = 255;
        ip1[i].ip[3] = i;
        DhcpAllocateIp(dhcp, ip1[i], &res);
        PrintIP4(res);
        printf("Count Free: %lu\n", DhcpCountFree(dhcp));
    }


    DhcpFreeIp(dhcp,ip1[50]);
    printf("Count Free After FREE: %lu\n", DhcpCountFree(dhcp));
    printf("status %d\n", DhcpAllocateIp(dhcp, ip1[30], &res));
    printf("Count Free After DhcpAllocateIp: %lu\n", DhcpCountFree(dhcp));

    PrintIP4(res);

    printf("\nDhcpCountFree\n");
    for (i = 1; i < SIZE; ++i)
    {
        printf("Free: ");
        PrintIP4(ip1[i]);
        ip1[i].ip[3] = i;

        DhcpFreeIp(dhcp,ip1[i]);
        printf("Count Free: %lu\n", DhcpCountFree(dhcp));
    }

    DhcpDestroy(dhcp);

    return SUCCESS;
}


void PrintIP4(ipv4_t ip)
{
    printf("ip:\n");
    printf("%d.", ip.ip[0]);
    printf("%d.", ip.ip[1]);
    printf("%d.", ip.ip[2]);
    printf("%d.", ip.ip[3]);
    printf("\n");
}
