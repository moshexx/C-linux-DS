#include <stdio.h> /* printf */

#include "dhcp.h"

/********************************Definitions***********************************/

#define RED printf("\033[0;31m")
#define GREEN printf("\033[0;32m")
#define RESET printf("\033[0m")

#define RUN_TEST(func, name) {\
            printf("%s: ", name);\
            if (1 == func)\
            {\
                GREEN;\
                printf("Success\n\n");\
                RESET;\
            }\
            else\
            {\
                RED;\
                printf("Failure\n\n");\
                RESET;\
            }\
        }

/*******************************Declarations***********************************/

static void TestCreateDestroy();
static int TestAllocate();
static int TestAllocZero();
static int TestAlloc2();
static int TestAllocBigSubnet();
static int TestAllocSmallSubnet();
static int TestFreeIP();
static int TestCountFree();

/******************************Test Functions**********************************/

int main()
{
	TestCreateDestroy();

	RUN_TEST(TestAllocate(), "Allocate");

	RUN_TEST(TestCountFree(), "Count Free");

	RUN_TEST(TestFreeIP(), "Free IP");


	return 0;
}

static void TestCreateDestroy()
{
	dhcp_t *d;
	ipv4_t subnet;

	subnet.ip[0] = 100;
	subnet.ip[1] = 101;
	subnet.ip[2] = 102;
	subnet.ip[3] = 0;

	d = DhcpCreate(subnet, 29);

	DhcpDestroy(d);
}

static int TestAllocate()
{
	int count_success = 0;
	int count_tests = 0;

	++count_tests;
	count_success += TestAllocZero();

	++count_tests;
	count_success += TestAlloc2();

	++count_tests;
	count_success += TestAllocBigSubnet();

	++count_tests;
	count_success += TestAllocSmallSubnet();

	return (count_success == count_tests);
}

static int TestAllocZero()
{
	int count_success = 0;
	int count_tests = 0;

	dhcp_t *d;
	ipv4_t subnet = {{101, 102, 103, 0}};

	ipv4_t result1, result2, result3, result4, result5, result6, result7,
					result8, result9, result10, result11, result12, result13;

	ipv4_t req_ip1 = {{101, 102, 103, 0}};
	ipv4_t req_ip2 = {{101, 102, 103, 0}};
	ipv4_t req_ip3 = {{101, 102, 103, 0}};
	ipv4_t req_ip4 = {{101, 102, 103, 0}};
	ipv4_t req_ip5 = {{101, 102, 103, 0}};
	ipv4_t req_ip6 = {{101, 102, 103, 0}};
	ipv4_t req_ip7 = {{101, 102, 103, 0}};
	ipv4_t req_ip8 = {{101, 102, 103, 0}};
	ipv4_t req_ip9 = {{101, 102, 103, 0}};
	ipv4_t req_ip10 = {{101, 102, 103, 0}};
	ipv4_t req_ip11 = {{101, 102, 103, 0}};
	ipv4_t req_ip12 = {{101, 102, 103, 0}};
	ipv4_t req_ip13 = {{101, 102, 103, 0}};

	d = DhcpCreate(subnet, 28);

	/*printf("size %ld\n", DhcpCountFree(d));*/

	++count_tests;
	count_success += (REPLACED == DhcpAllocateIp(d, req_ip1, &result1));
	++count_tests;
	count_success += (101 == result1.ip[0]);
	++count_tests;
	count_success += (102 == result1.ip[1]);
	++count_tests;
	count_success += (103 == result1.ip[2]);
	++count_tests;
	count_success += (1 == result1.ip[3]);

	++count_tests;
	count_success += (REPLACED == DhcpAllocateIp(d, req_ip2, &result2));
	++count_tests;
	count_success += (101 == result2.ip[0]);
	++count_tests;
	count_success += (102 == result2.ip[1]);
	++count_tests;
	count_success += (103 == result2.ip[2]);
	++count_tests;
	count_success += (2 == result2.ip[3]);

	++count_tests;
	count_success += (REPLACED == DhcpAllocateIp(d, req_ip3, &result3));
	++count_tests;
	count_success += (3 == result3.ip[3]);

	++count_tests;
	count_success += (REPLACED == DhcpAllocateIp(d, req_ip4, &result4));
	++count_tests;
	count_success += (4 == result4.ip[3]);

	++count_tests;
	count_success += (REPLACED == DhcpAllocateIp(d, req_ip5, &result5));
	++count_tests;
	count_success += (5 == result5.ip[3]);

	++count_tests;
	count_success += (REPLACED == DhcpAllocateIp(d, req_ip6, &result6));
	++count_tests;
	count_success += (6 == result6.ip[3]);

	++count_tests;
	count_success += (REPLACED == DhcpAllocateIp(d, req_ip7, &result7));
	++count_tests;
	count_success += (7 == result7.ip[3]);

	++count_tests;
	count_success += (REPLACED == DhcpAllocateIp(d, req_ip8, &result8));
	++count_tests;
	count_success += (8 == result8.ip[3]);

	++count_tests;
	count_success += (REPLACED == DhcpAllocateIp(d, req_ip9, &result9));
	++count_tests;
	count_success += (9 == result9.ip[3]);

	++count_tests;
	count_success += (REPLACED == DhcpAllocateIp(d, req_ip10, &result10));
	++count_tests;
	count_success += (10 == result10.ip[3]);

	++count_tests;
	count_success += (REPLACED == DhcpAllocateIp(d, req_ip11, &result11));
	++count_tests;
	count_success += (11 == result11.ip[3]);

	++count_tests;
	count_success += (REPLACED == DhcpAllocateIp(d, req_ip12, &result12));
	++count_tests;
	count_success += (12 == result12.ip[3]);

	++count_tests;
	count_success += (REPLACED == DhcpAllocateIp(d, req_ip13, &result13));
	++count_tests;
	count_success += (13 == result13.ip[3]);

	++count_tests;
	count_success += (FULL == DhcpAllocateIp(d, req_ip10, &result10));

	 printf("count_tests: %d, count_success %d\n", count_tests, count_success); 
	DhcpDestroy(d);

	return (count_success == count_tests);
}


static int TestAlloc2()
{
	int count_success = 0;
	int count_tests = 0;

	dhcp_t *d;
	ipv4_t subnet = {{101, 102, 103, 0}};

	ipv4_t result1, result2, result3, result4, result5, result6, result7,
					result8, result9, result10, result11, result12, result13;

	ipv4_t req_ip1 = {{101, 102, 103, 13}};
	ipv4_t req_ip2 = {{101, 102, 103, 1}};
	ipv4_t req_ip3 = {{101, 102, 103, 2}};
	ipv4_t req_ip4 = {{101, 102, 103, 3}};
	ipv4_t req_ip5 = {{101, 102, 103, 4}};
	ipv4_t req_ip6 = {{101, 102, 103, 5}};
	ipv4_t req_ip7 = {{101, 102, 103, 6}};
	ipv4_t req_ip8 = {{101, 102, 103, 7}};
	ipv4_t req_ip9 = {{101, 102, 103, 8}};
	ipv4_t req_ip10 = {{101, 102, 103, 1}};
	ipv4_t req_ip11 = {{101, 102, 103, 11}};
	ipv4_t req_ip12 = {{101, 102, 103, 12}};
	ipv4_t req_ip13 = {{101, 102, 103, 0}};

	d = DhcpCreate(subnet, 24);

	/*printf("size %ld\n", DhcpCountFree(d));*/

	++count_tests;
	count_success += (SUCCESS == DhcpAllocateIp(d, req_ip1, &result1));
	++count_tests;
	count_success += (101 == result1.ip[0]);
	++count_tests;
	count_success += (102 == result1.ip[1]);
	++count_tests;
	count_success += (103 == result1.ip[2]);
	++count_tests;
	count_success += (13 == result1.ip[3]);

	++count_tests;
	count_success += (SUCCESS == DhcpAllocateIp(d, req_ip2, &result2));

	++count_tests;
	count_success += (101 == result2.ip[0]);
	++count_tests;
	count_success += (102 == result2.ip[1]);
	++count_tests;
	count_success += (103 == result2.ip[2]);
	++count_tests;
	count_success += (1 == result2.ip[3]);

	++count_tests;
	count_success += (SUCCESS == DhcpAllocateIp(d, req_ip3, &result3));
	++count_tests;
	count_success += (2 == result3.ip[3]);

	++count_tests;
	count_success += (SUCCESS == DhcpAllocateIp(d, req_ip4, &result4));
	++count_tests;
	count_success += (3 == result4.ip[3]);

	++count_tests;
	count_success += (SUCCESS == DhcpAllocateIp(d, req_ip5, &result5));
	++count_tests;
	count_success += (4 == result5.ip[3]);

	++count_tests;
	count_success += (SUCCESS == DhcpAllocateIp(d, req_ip6, &result6));
	++count_tests;
	count_success += (5 == result6.ip[3]);

	++count_tests;
	count_success += (SUCCESS == DhcpAllocateIp(d, req_ip7, &result7));
	++count_tests;
	count_success += (6 == result7.ip[3]);

	++count_tests;
	count_success += (SUCCESS == DhcpAllocateIp(d, req_ip8, &result8));
	++count_tests;
	count_success += (7 == result8.ip[3]);

	++count_tests;
	count_success += (SUCCESS == DhcpAllocateIp(d, req_ip9, &result9));
	++count_tests;
	count_success += (8 == result9.ip[3]);

	++count_tests;
	count_success += (REPLACED == DhcpAllocateIp(d, req_ip10, &result10));
	++count_tests;
	count_success += (9 == result10.ip[3]);

	++count_tests;
	count_success += (SUCCESS == DhcpAllocateIp(d, req_ip11, &result11));
	++count_tests;
	count_success += (11 == result11.ip[3]);

	++count_tests;
	count_success += (SUCCESS == DhcpAllocateIp(d, req_ip12, &result12));
	++count_tests;
	count_success += (12 == result12.ip[3]);

	++count_tests;
	count_success += (REPLACED == DhcpAllocateIp(d, req_ip13, &result13));
	++count_tests;
	count_success += (10 == result13.ip[3]);

	/*printf("count_tests: %d, count_success %d\n", count_tests, count_success);*/

	DhcpDestroy(d);

	return (count_success == count_tests);
}


static int TestAllocBigSubnet()
{
	int count_success = 0;
	int count_tests = 0;

	dhcp_t *d, *d2, *d3;

	ipv4_t subnet = {{101, 102, 103, 248}};

	ipv4_t result1;

	ipv4_t req_ip1 = {{101, 102, 103, 0}};

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	d = DhcpCreate(subnet, 29);

	++count_tests;
	count_success += (FULL == DhcpAllocateIp(d, req_ip1, &result1));

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	d2 = DhcpCreate(subnet, 30);

	++count_tests;
	count_success += (REPLACED == DhcpAllocateIp(d2, req_ip1, &result1));

	++count_tests;
	count_success += (FULL == DhcpAllocateIp(d2, req_ip1, &result1));

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	d3 = DhcpCreate(subnet, 28);

	++count_tests;
	count_success += (REPLACED == DhcpAllocateIp(d3, req_ip1, &result1));
	++count_tests;
	count_success += (101 == result1.ip[0]);
	++count_tests;
	count_success += (102 == result1.ip[1]);
	++count_tests;
	count_success += (103 == result1.ip[2]);
	++count_tests;
	count_success += (249 == result1.ip[3]);

	/*printf("count_tests: %d, count_success %d\n", count_tests, count_success);*/

	DhcpDestroy(d);
	DhcpDestroy(d2);
	DhcpDestroy(d3);

	return (count_success == count_tests);
}

static int TestAllocSmallSubnet()
{
	int count_success = 0;
	int count_tests = 0;

	dhcp_t *d;
	ipv4_t subnet = {{128, 0, 0, 0}};

	ipv4_t result1, result2, result3, result4;

	ipv4_t req_ip1 = {{129, 102, 103, 104}};
	ipv4_t req_ip2 = {{128, 0, 0, 1}};
	ipv4_t req_ip3 = {{128, 0, 0, 0}};
	ipv4_t req_ip4 = {{255, 255, 255, 254}};

	d = DhcpCreate(subnet, 1);

	++count_tests;
	count_success += (SUCCESS == DhcpAllocateIp(d, req_ip1, &result1));

	++count_tests;
	count_success += (129 == result1.ip[0]);
	++count_tests;
	count_success += (102 == result1.ip[1]);
	++count_tests;
	count_success += (103 == result1.ip[2]);
	++count_tests;
	count_success += (104 == result1.ip[3]);

	++count_tests;
	count_success += (SUCCESS == DhcpAllocateIp(d, req_ip2, &result2));

	++count_tests;
	count_success += (128 == result2.ip[0]);
	++count_tests;
	count_success += (0 == result2.ip[1]);
	++count_tests;
	count_success += (0 == result2.ip[2]);
	++count_tests;
	count_success += (1 == result2.ip[3]);

	++count_tests;
	count_success += (REPLACED == DhcpAllocateIp(d, req_ip3, &result3));

	++count_tests;
	count_success += (128 == result3.ip[0]);
	++count_tests;
	count_success += (0 == result3.ip[1]);
	++count_tests;
	count_success += (0 == result3.ip[2]);
	++count_tests;
	count_success += (2 == result3.ip[3]);

	++count_tests;
	count_success += (FULL == DhcpAllocateIp(d, req_ip4, &result4));

	/*printf("%d\n", result1.ip[0]);
	printf("%d\n", result1.ip[1]);
	printf("%d\n", result1.ip[2]);
	printf("%d\n", result1.ip[3]);*/

	/*printf("count_tests: %d, count_success %d\n", count_tests, count_success);*/

	DhcpDestroy(d);

	return (count_success == count_tests);
}


static int TestFreeIP()
{
	int count_success = 0;
	int count_tests = 0;

	dhcp_t *d, *d1;
	ipv4_t subnet = {{101, 102, 103, 0}};

	ipv4_t result1, result2, result3, result4, result5, result6, result7,
					result8, result9, result10, result11, result12, result13,
															 result14, result15;

	ipv4_t req_ip1 = {{101, 102, 103, 0}};
	ipv4_t req_ip2 = {{101, 102, 103, 0}};
	ipv4_t req_ip3 = {{101, 102, 103, 0}};
	ipv4_t req_ip4 = {{101, 102, 103, 0}};
	ipv4_t req_ip5 = {{101, 102, 103, 0}};
	ipv4_t req_ip6 = {{101, 102, 103, 0}};
	ipv4_t req_ip7 = {{101, 102, 103, 0}};
	ipv4_t req_ip8 = {{101, 102, 103, 0}};
	ipv4_t req_ip9 = {{101, 102, 103, 0}};
	ipv4_t req_ip10 = {{101, 102, 103, 0}};
	ipv4_t req_ip11 = {{101, 102, 103, 0}};
	ipv4_t req_ip12 = {{101, 102, 103, 0}};
	ipv4_t req_ip13 = {{101, 102, 103, 0}};
	ipv4_t req_ip14 = {{101, 102, 103, 13}};
	ipv4_t req_ip15 = {{101, 102, 103, 1}};

	d = DhcpCreate(subnet, 28);

	DhcpAllocateIp(d, req_ip1, &result1);
	DhcpAllocateIp(d, req_ip2, &result2);
	DhcpAllocateIp(d, req_ip3, &result3);
	DhcpAllocateIp(d, req_ip4, &result4);
	DhcpAllocateIp(d, req_ip5, &result5);
	DhcpAllocateIp(d, req_ip6, &result6);
	DhcpAllocateIp(d, req_ip7, &result7);

	DhcpFreeIp(d, result3);

	++count_tests;
	count_success += (REPLACED == DhcpAllocateIp(d, req_ip1, &result1));

	DhcpAllocateIp(d, req_ip8, &result8);
	DhcpAllocateIp(d, req_ip9, &result9);
	DhcpAllocateIp(d, req_ip10, &result10);
	DhcpAllocateIp(d, req_ip11, &result11);
	DhcpAllocateIp(d, req_ip12, &result12);
	DhcpAllocateIp(d, req_ip13, &result13);

	DhcpFreeIp(d, result13);

	++count_tests;
	count_success += (SUCCESS == DhcpAllocateIp(d, req_ip14, &result14));

	/* printf("count_tests: %d, count_success %d\n", count_tests, count_success); */

	DhcpDestroy(d);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	d1 = DhcpCreate(subnet, 16);

	DhcpAllocateIp(d1, req_ip1, &result1); /* will be placed at 0 (because sunbet size 16) */
	DhcpAllocateIp(d1, req_ip2, &result2); /* will be placed at 1 */
	DhcpAllocateIp(d1, req_ip3, &result3); /* will be placed at 2 */

	DhcpFreeIp(d1, result2);

	++count_tests;
	count_success += (SUCCESS == DhcpAllocateIp(d1, req_ip15, &result15));

	DhcpDestroy(d1);

	/* printf("count_tests: %d, count_success %d\n", count_tests, count_success); */

	return (count_success == count_tests);
}

static int TestCountFree()
{
	int count_success = 0;
	int count_tests = 0;

	dhcp_t *d, *d1;
	ipv4_t subnet = {{101, 102, 103, 0}};

	ipv4_t result1, result2, result3, result4, result5, result6, result7,
					result8, result9, result10, result11, result12, result13;

	ipv4_t req_ip1 = {{101, 102, 103, 0}};
	ipv4_t req_ip2 = {{101, 102, 103, 0}};
	ipv4_t req_ip3 = {{101, 102, 103, 0}};
	ipv4_t req_ip4 = {{101, 102, 103, 0}};
	ipv4_t req_ip5 = {{101, 102, 103, 0}};
	ipv4_t req_ip6 = {{101, 102, 103, 0}};
	ipv4_t req_ip7 = {{101, 102, 103, 0}};
	ipv4_t req_ip8 = {{101, 102, 103, 0}};
	ipv4_t req_ip9 = {{101, 102, 103, 0}};
	ipv4_t req_ip10 = {{101, 102, 103, 0}};
	ipv4_t req_ip11 = {{101, 102, 103, 0}};
	ipv4_t req_ip12 = {{101, 102, 103, 0}};
	ipv4_t req_ip13 = {{101, 102, 103, 0}};

	d = DhcpCreate(subnet, 28);

	/*printf("size %ld\n", DhcpCountFree(d));*/

	++count_tests;
	count_success += (13 == DhcpCountFree(d));

	DhcpAllocateIp(d, req_ip1, &result1);

	++count_tests;
	count_success += (12 == DhcpCountFree(d));

	DhcpAllocateIp(d, req_ip2, &result2);
	DhcpAllocateIp(d, req_ip3, &result3);

	++count_tests;
	count_success += (10 == DhcpCountFree(d));

	DhcpAllocateIp(d, req_ip4, &result4);
	DhcpAllocateIp(d, req_ip5, &result5);
	DhcpAllocateIp(d, req_ip6, &result6);
	DhcpAllocateIp(d, req_ip7, &result7);

	++count_tests;
	count_success += (6 == DhcpCountFree(d));

	DhcpAllocateIp(d, req_ip8, &result8);
	DhcpAllocateIp(d, req_ip9, &result9);
	DhcpAllocateIp(d, req_ip10, &result10);
	DhcpAllocateIp(d, req_ip11, &result11);
	DhcpAllocateIp(d, req_ip12, &result12);

	++count_tests;
	count_success += (1 == DhcpCountFree(d));

	DhcpAllocateIp(d, req_ip13, &result13);

	++count_tests;
	count_success += (0 == DhcpCountFree(d));

	DhcpDestroy(d);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	d1 = DhcpCreate(subnet, 16);

	++count_tests;
	count_success += (65533 == DhcpCountFree(d1));

	DhcpAllocateIp(d1, req_ip1, &result1);

	++count_tests;
	count_success += (65532 == DhcpCountFree(d1));

	DhcpDestroy(d1);

	/* printf("count_tests: %d, count_success %d\n", count_tests, count_success); */

	return (count_success == count_tests);
}
